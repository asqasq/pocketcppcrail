/*
 * CppCrail: Native Crail
 *
 * Author: Patrick Stuedi  <stu@zurich.ibm.com>
 *
 * Copyright (C) 2015-2018, IBM Corporation
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "crail/client/crail_inputstream.h"

#include <iostream>
#include <memory>

#include "crail/client/namenode/getblock_response.h"
#include "crail/client/storage/narpc/narpc_storage_client.h"
#include "crail/client/storage/storage_client.h"
#include "crail/client/utils/crail_networking.h"

CrailInputstream::CrailInputstream(shared_ptr<NamenodeClient> namenode_client,
                                   shared_ptr<StorageCache> storage_cache,
                                   shared_ptr<BlockCache> block_cache,
                                   FileInfo file_info,
                                   unsigned long long position)
    : file_info_(file_info) {
  this->namenode_client_ = namenode_client;
  this->storage_cache_ = storage_cache;
  this->block_cache_ = block_cache;
  this->position_ = position;
}

CrailInputstream::~CrailInputstream() {}

Future<int> CrailInputstream::Read(shared_ptr<ByteBuffer> buf) {
  if (position_ >= file_info_.capacity()) {
    return Future<int>::Failure(-1);
  }

  int block_offset = position_ % kBlockSize;
  int block_remaining = kBlockSize - block_offset;
  unsigned long long file_remaining = file_info_.capacity() - position_;

  if (block_remaining < buf->remaining()) {
    buf->set_limit(buf->position() + block_remaining);
  }
  if (file_remaining < buf->remaining()) {
    buf->set_limit(buf->position() + file_remaining);
  }

  this->position_ += buf->remaining();

  BlockInfo block_info = block_cache_->GetBlock(position_);
  if (!block_info.valid()) {
    GetblockResponse get_block_res =
        namenode_client_
            ->GetBlock(file_info_.fd(), file_info_.token(), position_, 0)
            .get();

    if (get_block_res.error() < 0) {
      return Future<int>::Failure(-1);
    }

    block_info = get_block_res.block_info();
    block_cache_->PutBlock(position_, block_info);
  }

  int address = block_info.datanode().addr();
  int port = block_info.datanode().port();

  shared_ptr<StorageClient> storage_client = storage_cache_->Get(
      block_info.datanode().Key(), block_info.datanode().storage_class());
  if (storage_client->Connect(address, port) < 0) {
    return Future<int>::Failure(-1);
  }

  long long block_addr = block_info.addr() + block_offset;
  Future<int> storage_response =
      storage_client->ReadData(block_info.lkey(), block_addr, buf);

  return storage_response;
}

Future<int> CrailInputstream::Close() { return Future<int>::Failure(0); }

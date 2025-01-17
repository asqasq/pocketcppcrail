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

#include "crail/client/namenode/narpc/narpc_namenode_client.h"

#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "crail/client/crail_store.h"
#include "crail/client/namenode/create_request.h"
#include "crail/client/namenode/getblock_request.h"
#include "crail/client/namenode/ioctl_request.h"
#include "crail/client/namenode/lookup_request.h"
#include "crail/client/namenode/narpc/narpc_create_response.h"
#include "crail/client/namenode/narpc/narpc_getblock_response.h"
#include "crail/client/namenode/narpc/narpc_ioctl_response.h"
#include "crail/client/namenode/narpc/narpc_lookup_response.h"
#include "crail/client/namenode/narpc/narpc_remove_response.h"
#include "crail/client/namenode/narpc/narpc_void_response.h"
#include "crail/client/namenode/remove_request.h"
#include "crail/client/namenode/setfile_request.h"

NarpcNamenodeClient::NarpcNamenodeClient()
    : RpcClient(NarpcNamenodeClient::kNodelay) {}

NarpcNamenodeClient::~NarpcNamenodeClient() {}

Future<CreateResponse> NarpcNamenodeClient::Create(Filename &name, int type,
                                                   int storage_class,
                                                   int location_class,
                                                   int enumerable) {
  shared_ptr<CreateRequest> createReq = make_shared<CreateRequest>(
      name, type, storage_class, location_class, enumerable);
  RpcMessage request(createReq);

  shared_ptr<NarpcCreateResponse> getblockRes =
      make_shared<NarpcCreateResponse>(this);
  RpcMessage response(getblockRes);

  if (RpcClient::IssueRequest(request, response) < 0) {
    return Future<CreateResponse>::Failure();
  }
  return Future<CreateResponse>(getblockRes);
}

Future<LookupResponse> NarpcNamenodeClient::Lookup(Filename &name) {
  shared_ptr<LookupRequest> lookupReq = make_shared<LookupRequest>(name);
  RpcMessage request(lookupReq);

  shared_ptr<NarpcLookupResponse> lookupRes =
      make_shared<NarpcLookupResponse>(this);
  RpcMessage response(lookupRes);

  if (RpcClient::IssueRequest(request, response) < 0) {
    return Future<LookupResponse>::Failure();
  }
  return Future<LookupResponse>(lookupRes);
}

Future<GetblockResponse> NarpcNamenodeClient::GetBlock(long long fd,
                                                       long long token,
                                                       long long position,
                                                       long long capacity) {
  shared_ptr<GetblockRequest> get_block_req =
      make_shared<GetblockRequest>(fd, token, position, capacity);
  RpcMessage request(get_block_req);

  shared_ptr<NarpcGetBlockResponse> get_block_res =
      make_shared<NarpcGetBlockResponse>(this);
  RpcMessage response(get_block_res);

  if (RpcClient::IssueRequest(request, response) < 0) {
    return Future<GetblockResponse>::Failure();
  }
  return Future<GetblockResponse>(get_block_res);
}

Future<VoidResponse> NarpcNamenodeClient::SetFile(FileInfo &file_info,
                                                  bool close) {
  shared_ptr<SetfileRequest> set_file_req =
      make_shared<SetfileRequest>(file_info, close);
  RpcMessage request(set_file_req);

  shared_ptr<NarpcVoidResponse> set_file_res =
      make_shared<NarpcVoidResponse>(this);
  RpcMessage response(set_file_res);

  if (RpcClient::IssueRequest(request, response) < 0) {
    return Future<VoidResponse>::Failure();
  }
  return Future<VoidResponse>(set_file_res);
}

Future<RemoveResponse> NarpcNamenodeClient::Remove(Filename &name,
                                                   bool recursive) {
  shared_ptr<RemoveRequest> remove_req =
      make_shared<RemoveRequest>(name, recursive);
  RpcMessage request(remove_req);

  shared_ptr<NarpcRemoveResponse> remove_res =
      make_shared<NarpcRemoveResponse>(this);
  RpcMessage response(remove_res);

  if (RpcClient::IssueRequest(request, response) < 0) {
    return Future<RemoveResponse>::Failure();
  }
  return Future<RemoveResponse>(remove_res);
}

Future<IoctlResponse> NarpcNamenodeClient::Ioctl(unsigned char op,
                                                 Filename &name) {
  shared_ptr<IoctlRequest> ioctl_request = make_shared<IoctlRequest>(op, name);
  RpcMessage request(ioctl_request);

  shared_ptr<NarpcIoctlResponse> ioctl_response =
      make_shared<NarpcIoctlResponse>(this);
  RpcMessage response(ioctl_response);

  if (RpcClient::IssueRequest(request, response) < 0) {
    return Future<IoctlResponse>::Failure();
  }
  return Future<IoctlResponse>(ioctl_response);
}

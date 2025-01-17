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

#include "crail/client/storage/reflex/reflex_storage_client.h"

#include <iostream>

using namespace std;

ReflexStorageClient::ReflexStorageClient() {}

ReflexStorageClient::~ReflexStorageClient() {}

Future<int> ReflexStorageClient::WriteData(int key, long long address,
                                           shared_ptr<ByteBuffer> buf) {
  long long lba = linearBlockAddress(address, kReflexBlockSize);
  shared_ptr<ReflexFuture> future = Put(lba, buf);
  Future<int> future_tmp(nullptr);
  return future_tmp;
}

Future<int> ReflexStorageClient::ReadData(int key, long long address,
                                          shared_ptr<ByteBuffer> buf) {
  long long lba = linearBlockAddress(address, kReflexBlockSize);
  shared_ptr<ReflexFuture> future = Get(lba, buf);
  Future<int> future_tmp(nullptr);
  return future_tmp;
}

long long ReflexStorageClient::linearBlockAddress(long long address,
                                                  int sector_size) {
  if ((address % sector_size) == 0) {
    return address / (long)sector_size;
  } else {
    return -1;
  }
}

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

#ifndef NAMENODE_CLIENT_H
#define NAMENODE_CLIENT_H

#include <atomic>
#include <string>

#include "create_response.h"
#include "getblock_response.h"
#include "ioctl_response.h"
#include "lookup_response.h"
#include "metadata/filename.h"
#include "namenode_future.h"
#include "narpc/rpc_client.h"
#include "remove_response.h"
#include "void_response.h"

class NamenodeClient : public RpcClient {
public:
  NamenodeClient();
  virtual ~NamenodeClient();

  static const bool kNodelay = true;

  NamenodeFuture<CreateResponse> Create(Filename &name, int type,
                                        int storage_class, int location_class,
                                        int enumerable);
  NamenodeFuture<LookupResponse> Lookup(Filename &name);
  NamenodeFuture<GetblockResponse> GetBlock(long long fd, long long token,
                                            long long position,
                                            long long capacity);
  NamenodeFuture<VoidResponse> SetFile(shared_ptr<FileInfo> file_info,
                                       bool close);
  NamenodeFuture<RemoveResponse> Remove(Filename &name, bool recursive);
  NamenodeFuture<IoctlResponse> Ioctl(unsigned char op, Filename &name);

private:
  atomic<unsigned long long> counter_;
};

#endif /* NAMENODE_CLIENT_H */

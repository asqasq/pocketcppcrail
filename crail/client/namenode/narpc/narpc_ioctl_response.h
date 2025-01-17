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

#ifndef NARPC_IOCTL_RESPONSE_H
#define NARPC_IOCTL_RESPONSE_H

#include "crail/client/common/future.h"
#include "crail/client/namenode/ioctl_response.h"
#include "crail/client/narpc/rpc_client.h"

class NarpcIoctlResponse : public IoctlResponse,
                           public AsyncTask<IoctlResponse> {
public:
  NarpcIoctlResponse(RpcClient *client) : IoctlResponse(), client_(client) {}
  virtual ~NarpcIoctlResponse() {}

  IoctlResponse get() {
    client_->PollResponse();
    return *this;
  }

private:
  RpcClient *client_;
};

#endif /* NARPC_IOCTL_RESPONSE_H */

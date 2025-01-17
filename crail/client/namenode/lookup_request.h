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

#ifndef LOOKUP_REQUEST_H
#define LOOKUP_REQUEST_H

#include <string>

#include "crail/client/metadata/filename.h"
#include "crail/client/namenode/namenode_request.h"

using namespace std;

class LookupRequest : public NamenodeRequest {
public:
  LookupRequest(Filename &name);
  virtual ~LookupRequest();

  int Size() const {
    return NamenodeRequest::Size() + filename_.Size() + sizeof(int);
  }
  int Write(ByteBuffer &buf) const;
  int Update(ByteBuffer &buf);

  const Filename &filename() const { return filename_; }
  bool writeable() const { return writeable_; }

private:
  Filename filename_;
  bool writeable_;
};

#endif /* LOOKUP_REQUEST_H */

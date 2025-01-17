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

#include "crail/client/metadata/file_info.h"

#include <iostream>

#include "crail/client/common/file_type.h"

using namespace std;

FileInfo::FileInfo() {
  this->fd_ = -1;
  this->capacity_ = 0;
  this->node_type_ = static_cast<int>(FileType::Undefined);
  this->dir_offset_ = -1;
  this->modification_time_ = -1;
}

int FileInfo::Write(ByteBuffer &buf) const {
  buf.PutLong(fd_);
  buf.PutLong(capacity_);
  buf.PutInt(node_type_);
  buf.PutLong(dir_offset_);
  buf.PutLong(token_);
  buf.PutLong(modification_time_);

  return 0;
}

int FileInfo::Update(ByteBuffer &buf) {
  fd_ = buf.GetLong();
  capacity_ = buf.GetLong();
  node_type_ = buf.GetInt();
  dir_offset_ = buf.GetLong();
  token_ = buf.GetLong();
  modification_time_ = buf.GetLong();

  return 0;
}

int FileInfo::Dump() const {
  cout << "fd " << fd_ << ", capacity " << capacity_ << ", type " << node_type_
       << endl;
  return 0;
}

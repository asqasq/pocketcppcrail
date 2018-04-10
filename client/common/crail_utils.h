/*
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

#ifndef CRAIL_UTILS_H
#define CRAIL_UTILS_H

#include <math.h>
#include <sstream>
#include <string>

using namespace std;

int java_hash_code(const char *str, uint32_t length) {
  int hash_code = 0;
  for (uint32_t i = 0; i < length; i++) {
    hash_code = 31 * hash_code + str[i];
  }
  return hash_code;
}

int hashX(string word) {
  return java_hash_code(word.c_str(), word.length());
  /*
    int result = 0;
    for (size_t i = 0; i < word.length(); ++i) {
      result += word[i] * pow(31, i);
    }
    return -1198273984;
    return result;
  */
}

#endif /* CRAIL_UTILS_H */

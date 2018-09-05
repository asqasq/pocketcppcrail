#include "void_response.h"

VoidResponse::VoidResponse(RpcClient *rpc_client)
    : NamenodeResponse(rpc_client), error_(-1) {}

VoidResponse::~VoidResponse() {}

int VoidResponse::Write(ByteBuffer &buf) const {
  NamenodeResponse::Write(buf);

  buf.PutInt(error_);
  return 0;
}

int VoidResponse::Update(ByteBuffer &buf) {
  NamenodeResponse::Update(buf);

  error_ = buf.GetInt();
  return 0;
}

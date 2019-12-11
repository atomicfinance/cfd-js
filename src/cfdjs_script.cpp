// Copyright 2019 CryptoGarage
/**
 * @file cfdjs_script.cpp
 *
 * @brief cfd-apiで利用するScript関連の実装ファイル
 */
#include <string>

#include "cfdcore/cfdcore_common.h"
#include "cfdcore/cfdcore_exception.h"
#include "cfdcore/cfdcore_logger.h"
#include "cfdcore/cfdcore_script.h"

#include "cfdjs/cfdjs_script.h"
#include "cfdjs_internal.h"  // NOLINT

namespace cfd {
namespace js {
namespace api {

using cfd::core::CfdError;
using cfd::core::CfdException;
using cfd::core::logger::warn;
using cfd::core::Script;
using cfd::core::ScriptBuilder;
using cfd::core::ScriptElement;

ParseScriptResponseStruct ScriptStructApi::ParseScript(
    const ParseScriptRequestStruct& request) {
  auto call_func = [](const ParseScriptRequestStruct& request)
      -> ParseScriptResponseStruct {
    ParseScriptResponseStruct response;

    Script script(request.script);
    for (const auto& elem : script.GetElementList()) {
      std::string data;
      if (elem.IsOpCode()) {
        // Convert to OpCode string
        data = elem.GetOpCode().ToCodeString();
      } else {
        data = elem.ToString();
      }
      response.script_items.push_back(data);
    }
    return response;
  };

  ParseScriptResponseStruct result;
  result =
      ExecuteStructApi<ParseScriptRequestStruct, ParseScriptResponseStruct>(
          request, call_func, std::string(__FUNCTION__));
  return result;
}

CreateScriptResponseStruct ScriptStructApi::CreateScript(
    const CreateScriptRequestStruct& request) {
  auto call_func = [](const CreateScriptRequestStruct& request)
      -> CreateScriptResponseStruct {
    CreateScriptResponseStruct response;

    if(request.items.size() < 1) {
      warn(
          CFD_LOG_SOURCE, "empty script items.");
      throw CfdException(
          CfdError::kCfdIllegalArgumentError,
          "Failed to CreateScript. empty script items.");
    }

    ScriptBuilder sb = ScriptBuilder();
    for (const auto& item : request.items) {
      sb.AppendString(item);
    }
    Script script = sb.Build();

    response.hex = script.GetHex();
    return response;
  };

  CreateScriptResponseStruct result;
  result =
      ExecuteStructApi<CreateScriptRequestStruct, CreateScriptResponseStruct>(
          request, call_func, std::string(__FUNCTION__));
  return result;
}

}  // namespace api
}  // namespace js
}  // namespace cfd

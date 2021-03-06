// Copyright 2019 CryptoGarage
/**
 * @file cfdjs_node_addon.cpp
 *
 * @brief cfd node.js API implements file.
 */
#include <napi.h>  // NOLINT

#include <string>

#include "cfd/cfd_common.h"
#include "cfdjs/cfdjs_api_json.h"
#include "cfdjs/cfdjs_common.h"

using cfd::js::api::json::JsonMappingApi;
using Napi::CallbackInfo;
using Napi::Env;
using Napi::Function;
using Napi::Number;
using Napi::Object;
using Napi::String;
using Napi::TypeError;
using Napi::Value;

// -----------------------------------------------------------------------------
// API wrapper for node addon
// -----------------------------------------------------------------------------

namespace cfd {
namespace js {
namespace api {
namespace json {

/**
 * @brief NodeAddonのJSON APIテンプレート関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @param[in] call_function   cfdの呼び出し関数
 * @return 戻り値(JSON文字列)
 */
Value NodeAddonJsonApi(
    const CallbackInfo &information,
    std::function<std::string(const std::string &)> call_function) {
  Env env = information.Env();
  if (information.Length() < 1) {
    TypeError::New(env, "Invalid arguments.").ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!information[0].IsString()) {
    TypeError::New(env, "Wrong arguments.").ThrowAsJavaScriptException();
    return env.Null();
  }

  try {
    std::string json_message =
        call_function(information[0].As<String>().Utf8Value());
    return String::New(env, json_message.c_str());
  } catch (const std::exception &except) {
    // illegal route
    std::string errmsg = "exception=" + std::string(except.what());
    TypeError::New(env, errmsg).ThrowAsJavaScriptException();
    return env.Null();
  } catch (...) {
    // illegal route
    TypeError::New(env, "Illegal exception.").ThrowAsJavaScriptException();
    return env.Null();
  }
}

/**
 * @brief NodeAddonのJSON APIテンプレート関数(response only).
 * @param[in] information     node addon apiのコールバック情報
 * @param[in] call_function   cfdの呼び出し関数
 * @return 戻り値(JSON文字列)
 */
Value NodeAddonJsonResponseApi(
    const CallbackInfo &information,
    std::function<std::string()> call_function) {
  Env env = information.Env();
  try {
    std::string json_message = call_function();
    return String::New(env, json_message.c_str());
  } catch (const std::exception &except) {
    // illegal route
    std::string errmsg = "exception=" + std::string(except.what());
    TypeError::New(env, errmsg).ThrowAsJavaScriptException();
    return env.Null();
  } catch (...) {
    // illegal route
    TypeError::New(env, "Illegal exception.").ThrowAsJavaScriptException();
    return env.Null();
  }
}

/**
 * @brief GetSupportedFunctionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetSupportedFunction(const CallbackInfo &information) {
  return NodeAddonJsonResponseApi(
      information, JsonMappingApi::GetSupportedFunction);
}

/**
 * @brief CreateRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateRawTransaction);
}

/**
 * @brief AddRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value AddRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddRawTransaction);
}

/**
 * @brief DecodeRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value DecodeRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::DecodeRawTransaction);
}

/**
 * @brief ConvertEntropyToMnemonicのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ConvertEntropyToMnemonic(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::ConvertEntropyToMnemonic);
}

/**
 * @brief ConvertMnemonicToSeedのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ConvertMnemonicToSeed(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::ConvertMnemonicToSeed);
}

/**
 * @brief CreateAddressのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateAddress(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateAddress);
}

/**
 * @brief CreateMultisigのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateMultisig(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateMultisig);
}

/**
 * @brief GetAddressesFromMultisigのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetAddressesFromMultisig(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::GetAddressesFromMultisig);
}

/**
 * @brief GetAddressInfoのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetAddressInfo(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetAddressInfo);
}

/**
 * @brief ParseDescriptorのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ParseDescriptor(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::ParseDescriptor);
}

/**
 * @brief CreateDescriptorのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateDescriptor(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateDescriptor);
}

/**
 * @brief AppendDescriptorChecksumのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value AppendDescriptorChecksum(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::AppendDescriptorChecksum);
}

/**
 * @brief CreateSignatureHashのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateSignatureHash(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateSignatureHash);
}

/**
 * @brief ConvertAes の JSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ConvertAes(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::ConvertAes);
}

/**
 * @brief EncodeBase58 の JSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value EncodeBase58(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::EncodeBase58);
}

/**
 * @brief DecodeBase58 の JSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value DecodeBase58(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::DecodeBase58);
}

/**
 * @brief Encode the data by base64.
 * @param[in] request   request json string.
 * @return response json string.
 */
Value EncodeBase64(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::EncodeBase64);
}

/**
 * @brief Decode the data by base64.
 * @param[in] request   request json string.
 * @return response json string.
 */
Value DecodeBase64(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::DecodeBase64);
}

/**
 * @brief Hash message.
 * @param[in] request   request json string.
 * @return response json string.
 */
Value HashMessage(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::HashMessage);
}

/**
 * @brief EncodeSignatureByDer の JSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value EncodeSignatureByDer(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::EncodeSignatureByDer);
}

/**
 * @brief DecodeDerSignatureToRaw の JSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value DecodeDerSignatureToRaw(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::DecodeDerSignatureToRaw);
}

/**
 * @brief GetMnemonicWordlistのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetMnemonicWordlist(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetMnemonicWordlist);
}

/**
 * @brief GetExtkeyInfoのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetExtkeyInfo(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetExtkeyInfo);
}

/**
 * @brief GetPrivkeyFromExtkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetPrivkeyFromExtkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetPrivkeyFromExtkey);
}

/**
 * @brief GetPubkeyFromExtkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetPubkeyFromExtkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetPubkeyFromExtkey);
}

/**
 * @brief GetPrivkeyFromWifのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetPrivkeyFromWif(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetPrivkeyFromWif);
}

/**
 * @brief GetPrivkeyWifのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetPrivkeyWif(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetPrivkeyWif);
}

/**
  * @brief The JSON parameter function of TweakAddPrivkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value TweakAddPrivkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::TweakAddPrivkey);
}

/**
  * @brief The JSON parameter function of TweakMulPrivkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value TweakMulPrivkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::TweakMulPrivkey);
}

/**
  * @brief The JSON parameter function of NegatePrivkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value NegatePrivkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::NegatePrivkey);
}

/**
 * @brief GetPubkeyFromPrivkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetPubkeyFromPrivkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetPubkeyFromPrivkey);
}

/**
 * @brief GetCompressedPubkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetCompressedPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetCompressedPubkey);
}

/**
  * @brief The JSON parameter function of GetUncompressedPubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value GetUncompressedPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetUncompressedPubkey);
}

/**
  * @brief The JSON parameter function of CombinePubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value CombinePubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CombinePubkey);
}

/**
  * @brief The JSON parameter function of TweakAddPubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value TweakAddPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::TweakAddPubkey);
}

/**
  * @brief The JSON parameter function of TweakMulPubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value TweakMulPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::TweakMulPubkey);
}

/**
  * @brief The JSON parameter function of NegatePubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value NegatePubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::NegatePubkey);
}

/**
 * @brief CreateExtkeyFromSeedのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateExtkeyFromSeed(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateExtkeyFromSeed);
}

/**
 * @brief CreateExtkeyFromParentのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateExtkeyFromParent(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateExtkeyFromParent);
}

/**
 * @brief CreateExtkeyFromParentPathのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateExtkeyFromParentPath(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::CreateExtkeyFromParentPath);
}

/**
 * @brief CreateExtkeyFromParentKeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateExtkeyFromParentKey(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::CreateExtkeyFromParentKey);
}

/**
 * @brief CreateExtkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateExtkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateExtkey);
}

/**
 * @brief CreateExtPubkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateExtPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateExtPubkey);
}

/**
 * @brief CreateKeyPairのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateKeyPair(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateKeyPair);
}

/**
 * @brief ParseScriptのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ParseScript(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::ParseScript);
}

/**
 * @brief CreateScript のJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateScript(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateScript);
}

/**
 * @brief CreateMultisigScriptSig のJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateMultisigScriptSig(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::CreateMultisigScriptSig);
}

/**
 * @brief CalculateEcSignatureのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CalculateEcSignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CalculateEcSignature);
}

/**
 * @brief AddSignのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value AddSign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddSign);
}

/**
 * @brief AddPubkeyHashSignのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value AddPubkeyHashSign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddPubkeyHashSign);
}

/**
 * @brief SignWithPrivkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value SignWithPrivkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SignWithPrivkey);
}

/**
 * @brief AddScriptHashSignのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value AddScriptHashSign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddScriptHashSign);
}

/**
 * @brief UpdateWitnessStackのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value UpdateWitnessStack(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::UpdateWitnessStack);
}

/**
 * @brief GetWitnessStackNumのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetWitnessStackNum(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetWitnessStackNum);
}

/**
 * @brief AddMultisigSignのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value AddMultisigSign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddMultisigSign);
}

/**
 * @brief VerifySignatureのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value VerifySignature(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifySignature);
}

/**
 * @brief VerifySignのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value VerifySign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifySign);
}

/**
 * @brief EstimateFeeのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value EstimateFee(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::EstimateFee);
}

/**
 * @brief SelectUtxosのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value SelectUtxos(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SelectUtxos);
}

/**
 * @brief FundRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value FundRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::FundRawTransaction);
}

/**
 * @brief UpdateTxOutAmountのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value UpdateTxOutAmount(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::UpdateTxOutAmount);
}

/**
 * @brief GetSchnorrPubkeyFromPrivkeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetSchnorrPubkeyFromPrivkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::GetSchnorrPubkeyFromPrivkey);
}

/**
  * @brief The JSON parameter function of GetSchnorrPubkeyFromPubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value GetSchnorrPubkeyFromPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::GetSchnorrPubkeyFromPubkey);
}

/**
  * @brief The JSON parameter function of TweakAddSchnorrPubkeyFromPrivkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value TweakAddSchnorrPubkeyFromPrivkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::TweakAddSchnorrPubkeyFromPrivkey);
}

/**
  * @brief The JSON parameter function of TweakAddSchnorrPubkeyFromPubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value TweakAddSchnorrPubkeyFromPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::TweakAddSchnorrPubkeyFromPubkey);
}

/**
  * @brief The JSON parameter function of CheckTweakedSchnorrPubkey.
 * @param[in] information   node add on api callback information
  * @return json string
 */
Value CheckTweakedSchnorrPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::CheckTweakedSchnorrPubkey);
}

/**
 * @brief The JSON parameter function of SchnorrSign.
 * @param[in] information   node add on api callback information
 * @return json string
 */
Value SchnorrSign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SchnorrSign);
}

/**
 * @brief The JSON parameter function of SchnorrVerifyのJSON.
 * @param[in] information   node add on api callback information
 * @return json string
 */
Value SchnorrVerify(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SchnorrVerify);
}

/**
 * @brief The JSON parameter function of ComputeSigPointSchnorrPubkey.
 * @param[in] information   node add on api callback information
 * @return json string
 */
Value ComputeSigPointSchnorrPubkey(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::ComputeSigPointSchnorrPubkey);
}

/**
 * @brief The JSON parameter function of SignEcdsaAdaptor.
 * @param[in] information   node add on api callback information
 * @return json string
 */
Value SignEcdsaAdaptor(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SignEcdsaAdaptor);
}

/**
 * @brief The JSON parameter function of VerifyEcdsaAdaptor.
 * @param[in] information   node add on api callback information
 * @return json string
 */
Value VerifyEcdsaAdaptor(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifyEcdsaAdaptor);
}

/**
 * @brief The JSON parameter function of AdaptEcdsaAdaptor.
 * @param[in] information   node add on api callback information
 * @return json string
 */
Value AdaptEcdsaAdaptor(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AdaptEcdsaAdaptor);
}

/**
 * @brief The JSON parameter function of ExtractSecretEcdsaAdaptor.
 * @param[in] information   node add on api callback information
 * @return json string
 */
Value ExtractSecretEcdsaAdaptor(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::ExtractSecretEcdsaAdaptor);
}

/**
 * @brief Decode PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value DecodePsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::DecodePsbt);
}

/**
 * @brief Create PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value CreatePsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreatePsbt);
}

/**
 * @brief Convert transaction to PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value ConvertToPsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::ConvertToPsbt);
}

/**
 * @brief Join PSBTs.
 * @param[in] request_message the request json message
 * @return json string
 */
Value JoinPsbts(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::JoinPsbts);
}

/**
 * @brief Combine PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value CombinePsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CombinePsbt);
}

/**
 * @brief Finalize PSBT input.
 * @param[in] request_message the request json message
 * @return json string
 */
Value FinalizePsbtInput(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::FinalizePsbtInput);
}

/**
 * @brief Finalize and extract PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value FinalizePsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::FinalizePsbt);
}

/**
 * @brief Sign PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value SignPsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SignPsbt);
}

/**
 * @brief Verify PSBT sign.
 * @param[in] request_message the request json message
 * @return json string
 */
Value VerifyPsbtSign(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::VerifyPsbtSign);
}

/**
 * @brief Add PSBT input/output data.
 * @param[in] request_message the request json message
 * @return json string
 */
Value AddPsbtData(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::AddPsbtData);
}

/**
 * @brief Set PSBT data.
 * @param[in] request_message the request json message
 * @return json string
 */
Value SetPsbtData(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SetPsbtData);
}

/**
 * @brief Set PSBT record.
 * @param[in] request_message the request json message
 * @return json string
 */
Value SetPsbtRecord(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SetPsbtRecord);
}

/**
 * @brief Is finalized PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value IsFinalizedPsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::IsFinalizedPsbt);
}

/**
 * @brief Get PSBT utxos.
 * @param[in] request_message the request json message
 * @return json string
 */
Value GetPsbtUtxos(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetPsbtUtxos);
}

/**
 * @brief Fund PSBT.
 * @param[in] request_message the request json message
 * @return json string
 */
Value FundPsbt(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::FundPsbt);
}

#ifndef CFD_DISABLE_ELEMENTS

/**
 * @brief GetConfidentialAddressのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetConfidentialAddress(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetConfidentialAddress);
}

/**
 * @brief GetUnblindedAddressのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetUnblindedAddress(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetUnblindedAddress);
}

/**
 * @brief CreatePegInAddressのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreatePegInAddress(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreatePegInAddress);
}

/**
 * @brief ElementsCreateRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ElementsCreateRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::ElementsCreateRawTransaction);
}

/**
 * @brief ElementsAddRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ElementsAddRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::ElementsAddRawTransaction);
}

/**
 * @brief ElementsDecodeRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value ElementsDecodeRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::ElementsDecodeRawTransaction);
}

/**
 * @brief BlindRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value BlindRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::BlindRawTransaction);
}

/**
 * @brief UnblindRawTransactionのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value UnblindRawTransaction(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::UnblindRawTransaction);
}

/**
 * @brief SetRawIssueAssetのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value SetRawIssueAsset(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SetRawIssueAsset);
}

/**
 * @brief SetRawReissueAssetのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value SetRawReissueAsset(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SetRawReissueAsset);
}

/**
 * @brief CreateElementsSignatureHashのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateElementsSignatureHash(const CallbackInfo &information) {
  return NodeAddonJsonApi(
      information, JsonMappingApi::CreateElementsSignatureHash);
}

/**
 * @brief CreateRawPeginのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateRawPegin(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateRawPegin);
}

/**
 * @brief CreateRawPegoutのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateRawPegout(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateRawPegout);
}

/**
 * @brief GetIssuanceBlindingKeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetIssuanceBlindingKey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetIssuanceBlindingKey);
}

/**
 * @brief GetDefaultBlindingKeyのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetDefaultBlindingKey(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetDefaultBlindingKey);
}

/**
 * @brief CreateDestroyAmountのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value CreateDestroyAmount(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::CreateDestroyAmount);
}

/**
 * @brief SerializeLedgerFormatのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value SerializeLedgerFormat(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::SerializeLedgerFormat);
}

/**
 * @brief GetCommitmentのJSON API関数(request, response).
 * @param[in] information     node addon apiのコールバック情報
 * @return 戻り値(JSON文字列)
 */
Value GetCommitment(const CallbackInfo &information) {
  return NodeAddonJsonApi(information, JsonMappingApi::GetCommitment);
}
#endif  // CFD_DISABLE_ELEMENTS

/**
 * @brief JSON APIの生成初期化関数.
 * @param[in] env         環境情報
 * @param[out] exports    関数格納ポインタ
 */
void InitializeJsonApi(Env env, Object *exports) {
  cfd::Initialize();
  exports->Set(
      String::New(env, "GetSupportedFunction"),
      Function::New(env, GetSupportedFunction));
  exports->Set(
      String::New(env, "CreateRawTransaction"),
      Function::New(env, CreateRawTransaction));
  exports->Set(
      String::New(env, "AddRawTransaction"),
      Function::New(env, AddRawTransaction));
  exports->Set(
      String::New(env, "DecodeRawTransaction"),
      Function::New(env, DecodeRawTransaction));
  exports->Set(
      String::New(env, "ConvertEntropyToMnemonic"),
      Function::New(env, ConvertEntropyToMnemonic));
  exports->Set(
      String::New(env, "ConvertMnemonicToSeed"),
      Function::New(env, ConvertMnemonicToSeed));
  exports->Set(
      String::New(env, "CreateAddress"), Function::New(env, CreateAddress));
  exports->Set(
      String::New(env, "CreateMultisig"), Function::New(env, CreateMultisig));
  exports->Set(
      String::New(env, "GetAddressesFromMultisig"),
      Function::New(env, GetAddressesFromMultisig));
  exports->Set(
      String::New(env, "GetAddressInfo"), Function::New(env, GetAddressInfo));
  exports->Set(
      String::New(env, "ParseDescriptor"),
      Function::New(env, ParseDescriptor));
  exports->Set(
      String::New(env, "CreateDescriptor"),
      Function::New(env, CreateDescriptor));
  exports->Set(
      String::New(env, "AppendDescriptorChecksum"),
      Function::New(env, AppendDescriptorChecksum));
  exports->Set(
      String::New(env, "CreateSignatureHash"),
      Function::New(env, CreateSignatureHash));
  exports->Set(String::New(env, "ConvertAes"), Function::New(env, ConvertAes));
  exports->Set(
      String::New(env, "EncodeBase58"), Function::New(env, EncodeBase58));
  exports->Set(
      String::New(env, "DecodeBase58"), Function::New(env, DecodeBase58));
  exports->Set(
      String::New(env, "EncodeBase64"), Function::New(env, EncodeBase64));
  exports->Set(
      String::New(env, "DecodeBase64"), Function::New(env, DecodeBase64));
  exports->Set(
      String::New(env, "HashMessage"), Function::New(env, HashMessage));
  exports->Set(
      String::New(env, "EncodeSignatureByDer"),
      Function::New(env, EncodeSignatureByDer));
  exports->Set(
      String::New(env, "DecodeDerSignatureToRaw"),
      Function::New(env, DecodeDerSignatureToRaw));
  exports->Set(
      String::New(env, "GetWitnessStackNum"),
      Function::New(env, GetWitnessStackNum));
  exports->Set(String::New(env, "AddSign"), Function::New(env, AddSign));
  exports->Set(
      String::New(env, "AddPubkeyHashSign"),
      Function::New(env, AddPubkeyHashSign));
  exports->Set(
      String::New(env, "SignWithPrivkey"),
      Function::New(env, SignWithPrivkey));
  exports->Set(
      String::New(env, "AddScriptHashSign"),
      Function::New(env, AddScriptHashSign));
  exports->Set(
      String::New(env, "UpdateWitnessStack"),
      Function::New(env, UpdateWitnessStack));
  exports->Set(
      String::New(env, "AddMultisigSign"),
      Function::New(env, AddMultisigSign));
  exports->Set(
      String::New(env, "VerifySignature"),
      Function::New(env, VerifySignature));
  exports->Set(String::New(env, "VerifySign"), Function::New(env, VerifySign));
  exports->Set(
      String::New(env, "GetMnemonicWordlist"),
      Function::New(env, GetMnemonicWordlist));
  exports->Set(
      String::New(env, "GetExtkeyInfo"), Function::New(env, GetExtkeyInfo));
  exports->Set(
      String::New(env, "GetPrivkeyFromExtkey"),
      Function::New(env, GetPrivkeyFromExtkey));
  exports->Set(
      String::New(env, "GetPubkeyFromExtkey"),
      Function::New(env, GetPubkeyFromExtkey));
  exports->Set(
      String::New(env, "GetPrivkeyFromWif"),
      Function::New(env, GetPrivkeyFromWif));
  exports->Set(
      String::New(env, "GetPrivkeyWif"), Function::New(env, GetPrivkeyWif));
  exports->Set(
      String::New(env, "TweakAddPrivkey"),
      Function::New(env, TweakAddPrivkey));
  exports->Set(
      String::New(env, "TweakMulPrivkey"),
      Function::New(env, TweakMulPrivkey));
  exports->Set(
      String::New(env, "NegatePrivkey"), Function::New(env, NegatePrivkey));
  exports->Set(
      String::New(env, "GetPubkeyFromPrivkey"),
      Function::New(env, GetPubkeyFromPrivkey));
  exports->Set(
      String::New(env, "GetCompressedPubkey"),
      Function::New(env, GetCompressedPubkey));
  exports->Set(
      String::New(env, "GetUncompressedPubkey"),
      Function::New(env, GetUncompressedPubkey));
  exports->Set(
      String::New(env, "CombinePubkey"), Function::New(env, CombinePubkey));
  exports->Set(
      String::New(env, "TweakAddPubkey"), Function::New(env, TweakAddPubkey));
  exports->Set(
      String::New(env, "TweakMulPubkey"), Function::New(env, TweakMulPubkey));
  exports->Set(
      String::New(env, "NegatePubkey"), Function::New(env, NegatePubkey));
  exports->Set(
      String::New(env, "CreateExtkeyFromSeed"),
      Function::New(env, CreateExtkeyFromSeed));
  exports->Set(
      String::New(env, "CreateExtkeyFromParent"),
      Function::New(env, CreateExtkeyFromParent));
  exports->Set(
      String::New(env, "CreateExtkeyFromParentPath"),
      Function::New(env, CreateExtkeyFromParentPath));
  exports->Set(
      String::New(env, "CreateExtkeyFromParentKey"),
      Function::New(env, CreateExtkeyFromParentKey));
  exports->Set(
      String::New(env, "CreateExtkey"), Function::New(env, CreateExtkey));
  exports->Set(
      String::New(env, "CreateExtPubkey"),
      Function::New(env, CreateExtPubkey));
  exports->Set(
      String::New(env, "CreateKeyPair"), Function::New(env, CreateKeyPair));
  exports->Set(
      String::New(env, "ParseScript"), Function::New(env, ParseScript));
  exports->Set(
      String::New(env, "CreateScript"), Function::New(env, CreateScript));
  exports->Set(
      String::New(env, "CreateMultisigScriptSig"),
      Function::New(env, CreateMultisigScriptSig));
  exports->Set(
      String::New(env, "CalculateEcSignature"),
      Function::New(env, CalculateEcSignature));
  exports->Set(
      String::New(env, "EstimateFee"), Function::New(env, EstimateFee));
  exports->Set(
      String::New(env, "SelectUtxos"), Function::New(env, SelectUtxos));
  exports->Set(
      String::New(env, "FundRawTransaction"),
      Function::New(env, FundRawTransaction));
  exports->Set(
      String::New(env, "UpdateTxOutAmount"),
      Function::New(env, UpdateTxOutAmount));
  exports->Set(
      String::New(env, "GetSchnorrPubkeyFromPrivkey"),
      Function::New(env, GetSchnorrPubkeyFromPrivkey));
  exports->Set(
      String::New(env, "GetSchnorrPubkeyFromPubkey"),
      Function::New(env, GetSchnorrPubkeyFromPubkey));
  exports->Set(
      String::New(env, "TweakAddSchnorrPubkeyFromPrivkey"),
      Function::New(env, TweakAddSchnorrPubkeyFromPrivkey));
  exports->Set(
      String::New(env, "TweakAddSchnorrPubkeyFromPubkey"),
      Function::New(env, TweakAddSchnorrPubkeyFromPubkey));
  exports->Set(
      String::New(env, "CheckTweakedSchnorrPubkey"),
      Function::New(env, CheckTweakedSchnorrPubkey));
  exports->Set(
      String::New(env, "SchnorrSign"), Function::New(env, SchnorrSign));
  exports->Set(
      String::New(env, "SchnorrVerify"), Function::New(env, SchnorrVerify));
  exports->Set(
      String::New(env, "ComputeSigPointSchnorrPubkey"),
      Function::New(env, ComputeSigPointSchnorrPubkey));
  exports->Set(
      String::New(env, "SignEcdsaAdaptor"),
      Function::New(env, SignEcdsaAdaptor));
  exports->Set(
      String::New(env, "VerifyEcdsaAdaptor"),
      Function::New(env, VerifyEcdsaAdaptor));
  exports->Set(
      String::New(env, "AdaptEcdsaAdaptor"),
      Function::New(env, AdaptEcdsaAdaptor));
  exports->Set(
      String::New(env, "ExtractSecretEcdsaAdaptor"),
      Function::New(env, ExtractSecretEcdsaAdaptor));
  exports->Set(String::New(env, "DecodePsbt"), Function::New(env, DecodePsbt));
  exports->Set(String::New(env, "CreatePsbt"), Function::New(env, CreatePsbt));
  exports->Set(
      String::New(env, "ConvertToPsbt"), Function::New(env, ConvertToPsbt));
  exports->Set(String::New(env, "JoinPsbts"), Function::New(env, JoinPsbts));
  exports->Set(
      String::New(env, "CombinePsbt"), Function::New(env, CombinePsbt));
  exports->Set(
      String::New(env, "FinalizePsbtInput"),
      Function::New(env, FinalizePsbtInput));
  exports->Set(
      String::New(env, "FinalizePsbt"), Function::New(env, FinalizePsbt));
  exports->Set(String::New(env, "SignPsbt"), Function::New(env, SignPsbt));
  exports->Set(
      String::New(env, "VerifyPsbtSign"), Function::New(env, VerifyPsbtSign));
  exports->Set(
      String::New(env, "AddPsbtData"), Function::New(env, AddPsbtData));
  exports->Set(
      String::New(env, "SetPsbtData"), Function::New(env, SetPsbtData));
  exports->Set(
      String::New(env, "SetPsbtRecord"), Function::New(env, SetPsbtRecord));
  exports->Set(
      String::New(env, "IsFinalizedPsbt"),
      Function::New(env, IsFinalizedPsbt));
  exports->Set(
      String::New(env, "GetPsbtUtxos"), Function::New(env, GetPsbtUtxos));
  exports->Set(String::New(env, "FundPsbt"), Function::New(env, FundPsbt));
#ifndef CFD_DISABLE_ELEMENTS
  exports->Set(
      String::New(env, "GetConfidentialAddress"),
      Function::New(env, GetConfidentialAddress));
  exports->Set(
      String::New(env, "GetUnblindedAddress"),
      Function::New(env, GetUnblindedAddress));
  exports->Set(
      String::New(env, "CreatePegInAddress"),
      Function::New(env, CreatePegInAddress));
  exports->Set(
      String::New(env, "ElementsCreateRawTransaction"),
      Function::New(env, ElementsCreateRawTransaction));
  exports->Set(
      String::New(env, "ElementsAddRawTransaction"),
      Function::New(env, ElementsAddRawTransaction));
  exports->Set(
      String::New(env, "ElementsDecodeRawTransaction"),
      Function::New(env, ElementsDecodeRawTransaction));
  exports->Set(
      String::New(env, "BlindRawTransaction"),
      Function::New(env, BlindRawTransaction));
  exports->Set(
      String::New(env, "UnblindRawTransaction"),
      Function::New(env, UnblindRawTransaction));
  exports->Set(
      String::New(env, "SetRawIssueAsset"),
      Function::New(env, SetRawIssueAsset));
  exports->Set(
      String::New(env, "SetRawReissueAsset"),
      Function::New(env, SetRawReissueAsset));
  exports->Set(
      String::New(env, "CreateElementsSignatureHash"),
      Function::New(env, CreateElementsSignatureHash));
  exports->Set(
      String::New(env, "CreateRawPegin"), Function::New(env, CreateRawPegin));
  exports->Set(
      String::New(env, "CreateRawPegout"),
      Function::New(env, CreateRawPegout));
  exports->Set(
      String::New(env, "GetIssuanceBlindingKey"),
      Function::New(env, GetIssuanceBlindingKey));
  exports->Set(
      String::New(env, "GetDefaultBlindingKey"),
      Function::New(env, GetDefaultBlindingKey));
  exports->Set(
      String::New(env, "CreateDestroyAmount"),
      Function::New(env, CreateDestroyAmount));
  exports->Set(
      String::New(env, "SerializeLedgerFormat"),
      Function::New(env, SerializeLedgerFormat));
  exports->Set(
      String::New(env, "GetCommitment"), Function::New(env, GetCommitment));
#endif  // CFD_DISABLE_ELEMENTS
}

}  // namespace json
}  // namespace api
}  // namespace js
}  // namespace cfd

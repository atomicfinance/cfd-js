const Helper = require('../example_helper').default;
const GetResponse = Helper.getResponse;
const {
  CreateRawTransaction,
  CreateAddress,
  CreateSignatureHash,
  CalculateEcSignature,
  VerifySignature,
  AddScriptHashSign,
  VerifySign,
  DecodeRawTransaction,
} = Helper.getCfdjs();

const NET_TYPE = 'testnet';
const TXID = '985930b3c0d5b34d8f750c8b879cde6480224c5d39f093d66489e4d98ceb4a42';
const VOUT = 1;
const UTXO_AMOUNT = 10000;

// const MULTISIG_DESC = 'multi(2,tprv8ZgxMBicQKsPfFwzKCnWS4ijnUW4Txq6SCZ94TQr79EFUdcdeRbXzJGMUZPYD6W7Q3X52vfk6Y89UhYumZxanozp3S3vH8kDeo41FmzgwRc/44h/0h/0h/0/1,tprv8ZgxMBicQKsPfFwzKCnWS4ijnUW4Txq6SCZ94TQr79EFUdcdeRbXzJGMUZPYD6W7Q3X52vfk6Y89UhYumZxanozp3S3vH8kDeo41FmzgwRc/44h/0h/0h/0/2,tprv8ZgxMBicQKsPfFwzKCnWS4ijnUW4Txq6SCZ94TQr79EFUdcdeRbXzJGMUZPYD6W7Q3X52vfk6Y89UhYumZxanozp3S3vH8kDeo41FmzgwRc/44h/0h/0h/0/3)';
const MULTISIG_SCRIPT = '522102cd0d807c65b3a962cd98c84113ace64980818d58e92bbce746850fb3129465c52102b67a009a18e25b42df7e35c33beae1f12b2df9f13de6a79e340eaf8da6b9f08621032c47af28da861e12e8578ed92e229dad565414d2bb327e8ba4480ed44772ba5653ae';
const PRIVKEY_LIST = [
  'cUQ2SspDAynuTrYrQNoB1madLV5Wh7Qcti9bCM14437MVsqKroMe',
  'cNa8MLYnPS4nRLjPuRWvEKUpZZbbXgJoJ9147XGapvuzMKKvDKLc',
  'cRnmpKXUhyGCQh64B8UfCZ3QyabZBdAnXVREzxv1cPQjqPQLMqyM',
];
const PUBKEY_LIST = [
  '02cd0d807c65b3a962cd98c84113ace64980818d58e92bbce746850fb3129465c5',
  '02b67a009a18e25b42df7e35c33beae1f12b2df9f13de6a79e340eaf8da6b9f086',
  '032c47af28da861e12e8578ed92e229dad565414d2bb327e8ba4480ed44772ba56',
];

const example = async function() {
  console.log('\n===== createrawtransaction (script sign) =====');

  const tx = await GetResponse(CreateRawTransaction({
    version: 2,
    locktime: 0,
    txins: [{
      txid: TXID,
      vout: VOUT,
      sequence: 4294967295,
    }],
    txouts: [{
      address: 'tb1q6mk2afkqr9q5rht3r2hlm2g6lad776v0gfsft7',
      amount: UTXO_AMOUNT - 1000,
    }],
  }));
  console.log('\n*** base tx ***\n', tx);

  const hashTypes = ['p2sh', 'p2sh-p2wsh', 'p2wsh'];
  for (const hashType of hashTypes) {
    const utxoAddress = await GetResponse(CreateAddress({
      keyData: {
        hex: MULTISIG_SCRIPT,
        type: 'redeem_script',
      },
      network: NET_TYPE,
      hashType,
    }));
    console.log(`\n*** ${hashType} address ***\n`, utxoAddress);
    const address = utxoAddress.address;

    const sighash = await GetResponse(CreateSignatureHash({
      tx: tx.hex,
      txin: {
        txid: TXID,
        vout: VOUT,
        keyData: {
          hex: MULTISIG_SCRIPT,
          type: 'redeem_script',
        },
        amount: UTXO_AMOUNT,
        hashType: (hashType == 'p2sh-p2wsh') ? 'p2wsh' : hashType,
        sighashType: 'all',
        sighashAnyoneCanPay: false,
      },
    }));
    console.log(`\n*** ${hashType} signature hash ***\n`, sighash);

    const signParamList = [];
    let count = 0;
    for (const index of [0, 1]) {
      const pubkey = PUBKEY_LIST[index];
      const privkeyWif = PRIVKEY_LIST[index];
      ++count;

      const signature = await GetResponse(CalculateEcSignature({
        sighash: sighash.sighash,
        privkeyData: {
          privkey: privkeyWif,
          wif: true,
          network: NET_TYPE,
        },
        isGrindR: true,
      }));
      console.log(`\n*** ${hashType} signature${count} ***\n`, signature);

      const verifySignature = await GetResponse(VerifySignature({
        tx: tx.hex,
        txin: {
          txid: TXID,
          vout: VOUT,
          signature: signature.signature,
          pubkey,
          redeemScript: MULTISIG_SCRIPT,
          hashType: (hashType == 'p2sh-p2wsh') ? 'p2wsh' : hashType,
          sighashType: 'all',
          sighashAnyoneCanPay: false,
          amount: UTXO_AMOUNT,
        },
      }));
      console.log(`\n*** ${hashType} signature verify${count} ***\n`, verifySignature);
      if (!verifySignature.success) {
        throw new Error('verify fail.');
      }

      signParamList.push({
        hex: signature.signature,
        type: 'sign',
        derEncode: true,
        sighashType: 'all',
        sighashAnyoneCanPay: false,
      });
    }

    const signedTx = await GetResponse(AddScriptHashSign({
      tx: tx.hex,
      txin: {
        txid: TXID,
        vout: VOUT,
        signParam: signParamList,
        hashType,
        redeemScript: MULTISIG_SCRIPT,
      },
    }));
    console.log(`\n*** ${hashType} signed tx ***\n`, signedTx);

    const verifySign = await GetResponse(VerifySign({
      tx: signedTx.hex,
      txins: [{
        txid: TXID,
        vout: VOUT,
        address,
        amount: UTXO_AMOUNT,
      }],
    }));
    console.log(`\n*** ${hashType} verify sign ***\n`, verifySign);
    if (!verifySign.success) {
      throw new Error('verify fail.');
    }

    const decodeTx = await GetResponse(DecodeRawTransaction({
      hex: signedTx.hex,
      network: NET_TYPE,
    }));
    console.log(`\n*** ${hashType} decode tx ***\n`,
        JSON.stringify(decodeTx, (key, value) =>
            typeof value === 'bigint' ? value.toString() : value, '  '));
  }
};

module.exports = example;

if ((process.argv.length > 1) && (process.argv[1].indexOf('example.js') == -1)) {
  example();
}

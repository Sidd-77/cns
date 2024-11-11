const crypto = require("crypto");

// Generate DSA keys (public and private)
function generateKeys() {
  const { publicKey, privateKey } = crypto.generateKeyPairSync("dsa", {
    modulusLength: 1024, // Key size
    divisorLength: 160,
    publicKeyEncoding: {
      type: "spki",
      format: "pem",
    },
    privateKeyEncoding: {
      type: "pkcs8",
      format: "pem",
    },
  });
  return { publicKey, privateKey };
}

// Sign the message using the private key
function signMessage(privateKey, message) {
  const sign = crypto.createSign("SHA256");
  sign.update(message);
  sign.end();
  const signature = sign.sign(privateKey, "hex");
  return signature;
}

// Verify the signature using the public key
function verifySignature(publicKey, message, signature) {
  const verify = crypto.createVerify("SHA256");
  verify.update(message);
  verify.end();
  const isValid = verify.verify(publicKey, signature, "hex");
  return isValid;
}

function main() {
  const { publicKey, privateKey } = generateKeys();

  // Prompt for a message
  const readline = require("readline").createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  readline.question("Enter the message: ", (message) => {
    // Sign the message
    const signature = signMessage(privateKey, message);
    console.log(`Signature: ${signature}`);

    // Verify the signature
    const isValid = verifySignature(publicKey, message, signature);
    if (isValid) {
      console.log("The signature is valid.");
    } else {
      console.log("The signature is invalid.");
    }
    readline.close();
  });
}

main();

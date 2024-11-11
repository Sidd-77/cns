const crypto = require("crypto");
const fs = require("fs");
const readline = require("readline").createInterface({
  input: process.stdin,
  output: process.stdout,
});

let publicKey, privateKey;

// Generate DSA keys (public and private)
function generateKeys() {
  const keys = crypto.generateKeyPairSync("dsa", {
    modulusLength: 1024,
    divisorLength: 160,
    publicKeyEncoding: { type: "spki", format: "pem" },
    privateKeyEncoding: { type: "pkcs8", format: "pem" },
  });
  publicKey = keys.publicKey;
  privateKey = keys.privateKey;
  console.log("Keys generated successfully.");
  console.log("Public Key:\n", publicKey);
  console.log("Private Key:\n", privateKey);
  showMenu();
}

// Sign the message from "message.txt" using the private key
function signMessageFromFile() {
  const filePath = "message.txt";
  if (!fs.existsSync(filePath)) {
    console.error("File 'message.txt' not found.");
    showMenu();
    return;
  }

  const message = fs.readFileSync(filePath, "utf8");
  const sign = crypto.createSign("SHA256");
  sign.update(message);
  sign.end();
  const signature = sign.sign(privateKey, "hex");

  // Save the signature to "signature.txt"
  fs.writeFileSync("signature.txt", signature);
  console.log("Signature saved to 'signature.txt'");
  showMenu();
}

// Verify the signature using the public key and "message.txt"
function verifySignatureFromFile() {
  const messageFile = "message.txt";
  const signatureFile = "signature.txt";

  if (!fs.existsSync(messageFile)) {
    console.error("File 'message.txt' not found.");
    showMenu();
    return;
  }

  if (!fs.existsSync(signatureFile)) {
    console.error("File 'signature.txt' not found.");
    showMenu();
    return;
  }

  const message = fs.readFileSync(messageFile, "utf8");
  const signature = fs.readFileSync(signatureFile, "utf8");
  const verify = crypto.createVerify("SHA256");
  verify.update(message);
  verify.end();
  const isValid = verify.verify(publicKey, signature, "hex");

  if (isValid) {
    console.log("The signature is valid.");
  } else {
    console.log("The signature is invalid.");
  }
  showMenu();
}

// Display the menu and handle user input
function showMenu() {
  console.log("\nSelect an option:");
  console.log("1. Generate Keys");
  console.log("2. Sign 'message.txt'");
  console.log("3. Verify 'signature.txt' against 'message.txt'");
  console.log("4. Exit");

  readline.question("Enter your choice: ", (choice) => {
    switch (choice) {
      case "1":
        generateKeys();
        break;
      case "2":
        if (!privateKey) {
          console.log("Please generate keys first.");
          showMenu();
        } else {
          signMessageFromFile();
        }
        break;
      case "3":
        if (!publicKey) {
          console.log("Please generate keys first.");
          showMenu();
        } else {
          verifySignatureFromFile();
        }
        break;
      case "4":
        console.log("Exiting program.");
        readline.close();
        break;
      default:
        console.log("Invalid choice. Please try again.");
        showMenu();
    }
  });
}

// Start the program
showMenu();

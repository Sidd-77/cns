const crypto = require('crypto');

// Encrypt function
function encrypt(plaintext, password) {
  // Generate random 16-byte salt and derive key using PBKDF2
  const salt = crypto.randomBytes(16);
  const key = crypto.pbkdf2Sync(password, salt, 100000, 32, 'sha256');

  // Generate random 16-byte IV
  const iv = crypto.randomBytes(16);

  // Initialize AES-256-CBC cipher
  const cipher = crypto.createCipheriv('aes-256-cbc', key, iv);

  // Encrypt the plaintext and get it in Buffer form
  const encrypted = Buffer.concat([cipher.update(plaintext, 'utf8'), cipher.final()]);

  // Return concatenated salt, iv, and encrypted data as a hex string
  return Buffer.concat([salt, iv, encrypted]).toString('hex');
}

// Decrypt function
function decrypt(encryptedHex, password) {
  // Convert hex string to buffer and extract components
  const encryptedData = Buffer.from(encryptedHex, 'hex');
  const salt = encryptedData.slice(0, 16);
  const iv = encryptedData.slice(16, 32);
  const actualCiphertext = encryptedData.slice(32);

  // Derive key using the same salt
  const key = crypto.pbkdf2Sync(password, salt, 100000, 32, 'sha256');

  // Initialize AES-256-CBC decipher
  const decipher = crypto.createDecipheriv('aes-256-cbc', key, iv);

  // Decrypt and convert to UTF-8
  const decrypted = Buffer.concat([decipher.update(actualCiphertext), decipher.final()]);
  return decrypted.toString('utf8');
}

// Example usage
const password = "strong_password";
const plaintext = "Hello, AES encryption!";

// Encrypt the plaintext
const encryptedData = encrypt(plaintext, password);
console.log("Encrypted:", encryptedData);

// Decrypt the encrypted data
const decryptedText = decrypt(encryptedData, password);
console.log("Decrypted:", decryptedText);

const crypto = require('crypto');

// Encrypt function using DES in ECB mode
function encrypt(message, key) {
    // Generate an 8-byte DES key from the hashed password (MD5) and truncate to 8 bytes
    const desKey = crypto.createHash('md5').update(key).digest('hex').substring(0, 8);

    try {
        const cipher = crypto.createCipheriv('des-ecb', desKey, null);
        let encrypted = cipher.update(message, 'utf8', 'base64');
        encrypted += cipher.final('base64');

        console.log("Encrypted Message:", encrypted);
        return encrypted;
    } catch (error) {
        console.error('Error during encryption:', error);
        return null;
    }
}

// Decrypt function using DES in ECB mode
function decrypt(encryptedMessage, key) {
    // Generate the same 8-byte DES key from the hashed password (MD5) and truncate to 8 bytes
    const desKey = crypto.createHash('md5').update(key).digest('hex').substring(0, 8);

    try {
        const decipher = crypto.createDecipheriv('des-ecb', desKey, null);
        let decrypted = decipher.update(encryptedMessage, 'base64', 'utf8');
        decrypted += decipher.final('utf8');

        console.log("Decrypted Message:", decrypted);
        return decrypted;
    } catch (error) {
        console.error('Error during decryption:', error);
        return null;
    }
}

// Example usage
const message = "Hello, DES encryption!";
const key = "strong_password";

// Encrypt the message
const encryptedMessage = encrypt(message, key);

// Decrypt the encrypted message
if (encryptedMessage) {
    decrypt(encryptedMessage, key);
}

// run this before running this code
// export NODE_OPTIONS=--openssl-legacy-provider

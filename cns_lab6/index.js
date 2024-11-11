const express = require('express');
const bodyParser = require('body-parser');
const crypto = require('crypto');

// Initialize express
const app = express();
const PORT = 3000;

// Use middleware to parse JSON request bodies
app.use(bodyParser.json());
app.use(express.static(__dirname + '/public'));

// AES Encryption
app.post('/encrypt', (req, res) => {
    const { message, key } = req.body;

    try {
        const algorithm = 'aes-256-cbc';
        const keyBuffer = crypto.createHash('sha256').update(key).digest();
        const iv = crypto.randomBytes(16); // Initialization vector for AES-CBC mode

        const cipher = crypto.createCipheriv(algorithm, keyBuffer, iv);
        let encrypted = cipher.update(message, 'utf8', 'hex');
        encrypted += cipher.final('hex');

        // Send encrypted message back to the client
        const encryptedMessage = iv.toString('hex') + ':' + encrypted;
        res.json({ encryptedMessage });
    } catch (error) {
        console.error('Error during encryption:', error);
        res.status(500).json({ error: 'Encryption failed' });
    }
});

// AES Decryption
app.post('/decrypt', (req, res) => {
    const { encryptedMessage, key } = req.body;

    try {
        const algorithm = 'aes-256-cbc';
        const keyBuffer = crypto.createHash('sha256').update(key).digest();
        const [ivHex, encrypted] = encryptedMessage.split(':');
        const iv = Buffer.from(ivHex, 'hex');

        const decipher = crypto.createDecipheriv(algorithm, keyBuffer, iv);
        let decrypted = decipher.update(encrypted, 'hex', 'utf8');
        decrypted += decipher.final('utf8');

        // Send decrypted message back to the client
        res.json({ decryptedMessage: decrypted });
    } catch (error) {
        console.error('Error during decryption:', error);
        res.status(500).json({ error: 'Decryption failed' });
    }
});

// Start server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});

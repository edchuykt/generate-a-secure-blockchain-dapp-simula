#ifndef W4MU_GENERATE_A_SECU_CPP
#define W4MU_GENERATE_A_SECU_CPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <openssl/sha.h>

using namespace std;

// Blockchain structure
struct Block {
    string data;
    string hash;
    string prevHash;
    int timestamp;
    int nonce;
};

// Blockchain class
class Blockchain {
private:
    vector<Block> chain;
    int difficulty;

public:
    Blockchain(int difficulty) : difficulty(difficulty) {
        // Genesis block
        Block genesisBlock;
        genesisBlock.data = "Genesis Block";
        genesisBlock.hash = calculateHash(genesisBlock);
        genesisBlock.prevHash = "0";
        genesisBlock.timestamp = time(0);
        genesisBlock.nonce = 0;
        chain.push_back(genesisBlock);
    }

    string calculateHash(Block block) {
        // SHA-256 hash function
        unsigned char hash[SHA256_DIGEST_LENGTH];
        string data = to_string(block.timestamp) + block.data + block.prevHash + to_string(block.nonce);
        SHA256((unsigned char*)data.c_str(), data.size(), hash);
        string hashStr = "";
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            char buffer[3];
            sprintf(buffer, "%02x", hash[i]);
            hashStr += buffer;
        }
        return hashStr;
    }

    void addBlock(string data) {
        Block newBlock;
        newBlock.data = data;
        newBlock.prevHash = getLatestBlock().hash;
        newBlock.timestamp = time(0);
        newBlock.nonce = 0;
        newBlock.hash = calculateHash(newBlock);

        // Proof-of-work
        while (newBlock.hash.substr(0, difficulty).compare(string(difficulty, '0'))) {
            newBlock.nonce++;
            newBlock.hash = calculateHash(newBlock);
        }

        chain.push_back(newBlock);
    }

    Block getLatestBlock() {
        return chain.back();
    }

    void displayChain() {
        for (Block block : chain) {
            cout << "Data: " << block.data << endl;
            cout << "Hash: " << block.hash << endl;
            cout << "Prev Hash: " << block.prevHash << endl;
            cout << "Timestamp: " << block.timestamp << endl;
            cout << "Nonce: " << block.nonce << endl;
            cout << "---------------" << endl;
        }
    }
};

// dApp Simulator class
class dAppSimulator {
private:
    Blockchain blockchain;

public:
    dAppSimulator(int difficulty) : blockchain(difficulty) {}

    void simulateTransaction(string data) {
        blockchain.addBlock(data);
    }

    void displayBlockchain() {
        blockchain.displayChain();
    }
};

int main() {
    dAppSimulator simulator(4);
    simulator.simulateTransaction("Transaction 1");
    simulator.simulateTransaction("Transaction 2");
    simulator.displayBlockchain();
    return 0;
}

#endif // W4MU_GENERATE_A_SECU_CPP
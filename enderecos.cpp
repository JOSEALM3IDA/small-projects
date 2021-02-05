/* Feito em conjunto com TheForgottened
 * Objetivo: Buscar informação sobre SUBNETS, dado um IP e uma SUBNET MASK
 */

#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#define IP vector<bitset<8>>

using namespace std;

IP strToBits(string str) {
    int pos = 0;
    string token;
    string del = ".";

    vector<string> strIP;
    while (str.size() != 0) {
        pos = str.find(del);
        token = str.substr(0, pos);
        strIP.push_back(token);
        str.erase(0, pos + del.length());
    }

    if (strIP.size() != 4) {
        cout << "IP Invalido!" << endl;
        exit(-1);
    }

    IP bitsIP;
    for (string num : strIP) {
        int novo;
        if (num.length() > 0) {
            novo = stoi(num);
            if (novo < 0 || novo > 255) {
                cout << "IP Invalido!" << endl;
                exit(-1);
            }
        } else {
            cout << "IP Invalido!" << endl;
            exit(-1);
        }

        bitset<8> bitnum(novo);
        bitsIP.push_back(bitnum);
    }

    return bitsIP;
}

ostream& operator<<(ostream& out, IP& ip) {
    for (int i = 0; i < 4; i++) {
        out << ip[i].to_ulong();
        if (i != 3)
            out << '.';
    }
    return out;       
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "\nInsira IP (dotted decimal): ";

        string ip;
        cin >> ip;
        ip += '.';
        
        IP bitsIP = strToBits(ip);

        ofstream file;
        file.open("output.txt");

        cout << endl << "IP Inserido: " << bitsIP;
        file << "IP Inserido: " << bitsIP;

        int i;
        for (i = 7; i >= 0; i--)
            if (bitsIP[0][i] == 0)
                break;
        
        char classe = 7 - i + 'A';
        cout << " (Classe " << classe;
        file << " (Classe " << classe;
        if (classe == 'A' && bitsIP[0].to_ulong() == 10) {
            cout << " - Privado)";
            file << " - Privado)" << endl;
        } else if (classe == 'B' && bitsIP[0].to_ulong() == 172 && bitsIP[1].to_ulong() >= 16 && bitsIP[1].to_ulong() <= 31) {
            cout << " - Privado)";
            file << " - Privado)" << endl;
        } else if (classe == 'C' && bitsIP[0].to_ulong() == 192 && bitsIP[1].to_ulong() == 168) {
            cout << " - Privado)";
            file << " - Privado)" << endl;
        } else {
            cout << " - Publico)";
            file << " - Publico)" << endl;
        }

        IP bitsNetMask;
        int tamNetMask;
        switch (classe) {
            case 'A':
                bitsNetMask = strToBits("255.0.0.0.");
                tamNetMask = 8;
                break;
                
            case 'B':
                bitsNetMask = strToBits("255.255.0.0.");
                tamNetMask = 16;
                break;
                
            case 'C':
                bitsNetMask = strToBits("255.255.255.0.");
                tamNetMask = 24;
                break;
                
            default:
                cout << " - Sem Default Mask";
                file << " - Sem Default Mask";
                exit(0);
        }
            
        cout << "\n\nInsira SUBNET Mask (dotted decimal): ";
        string subMask;
        cin >> subMask;
        subMask += '.';
        
        IP bitsSubMask = strToBits(subMask);

        int tamHost = 0;
        for (auto bits : bitsSubMask)
            for (int i = 7; i >= 0; i--)
                if (bits[i] == 1) {
                    if (tamHost != 0) {
                        cout << "SUBNET Mask Invalida!" << endl;
                        exit(-1);
                    }
                } else
                    tamHost++;

        int tamSubnet = 32 - tamNetMask - tamHost;
        int nSubNet = pow(2, tamSubnet);
        int nHost = pow(2, tamHost);

        cout << "\nNet mask: " << bitsNetMask << " (/" << tamNetMask << ")" << endl;
        cout << "Subnet mask: " << bitsSubMask << " (/" << tamSubnet + tamNetMask << ")" << " - Numero de subnets: " << nSubNet << endl;
        cout << "HostID: " << tamHost << " bits - IPs uteis por rede: " << nHost - 2 << endl;
        file << "Net mask: " << bitsNetMask << " (/" << tamNetMask << ")" << endl;
        file << "Subnet mask: " << bitsSubMask << " (/" << tamSubnet + tamNetMask << ")" << " - Numero de subnets: " << nSubNet << endl;
        file << "HostID: " << tamHost << " bits - IPs uteis por rede: " << nHost - 2 << endl;

        cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
        file << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;

        IP IPAtual = bitsIP;

        for (int j = 0; j < 4; j++)
            for (int i = 7; i >= 0; i--)
                IPAtual[j][i] = IPAtual[j][i] & bitsNetMask[j][i];

        int faltam;
        bitset<32> hostBits;
        for (int rede = 0; rede < nSubNet; rede++) {
            file << "Rede " << rede + 1 << endl << IPAtual << " (IP de Rede)" << endl;

            for (int host = 0; host < nHost; host++) {
                faltam = tamHost;
                hostBits = 0;

                while (faltam != 0) {
                    for (int j = 3; j >= 0; j--) // Percorrer os 4 bytes
                        for (int i = 0; i < 8; i++) // Percorrer cada bit
                            if (faltam == 0) {
                                break;
                            } else {
                                hostBits[tamHost - (faltam--)] = IPAtual[j][i];
                            }

                        if (faltam == 0)
                            break;
                }

                faltam = tamHost;

                if ((hostBits.to_ulong() + 1) == pow(2, tamHost)) {
                    
                    for (int j = 0; j < 4; j++) // Percorrer os 4 bytes
                        for (int i = 7; i >= 0; i--) // Percorrer cada bit
                            hostBits[(j * 8) + i] = IPAtual[3 - j][i];

                    hostBits = hostBits.to_ulong() + 1;

                    file << endl;

                    for (int j = 0; j < 4; j++) // Percorrer os 4 bytes
                        for (int i = 7; i >= 0; i--) // Percorrer cada bit
                            IPAtual[3 - j][i] = hostBits[(j * 8) + i];
                    

                    break;
                } else {
                    hostBits = hostBits.to_ulong() + 1;

                    while (faltam != 0) {
                        for (int j = 3; j >= 0; j--) // Percorrer os 4 bytes
                            for (int i = 0; i < 8; i++) // Percorrer cada bit
                                if (faltam == 0) {
                                    break;
                                } else
                                    IPAtual[j][i] = hostBits[tamHost - (faltam--)];

                            if (faltam == 0)
                                break;
                    }

                    if (hostBits.to_ulong() + 1 == pow(2, tamHost)) {
                        file << IPAtual << " (IP de Difusao)" << endl;
                    }
                }
            }
        }

        file.close();
        return 0;
    } else {
        string ip = argv[1];
        ip += '.';
        
        IP bitsIP = strToBits(ip);

        ofstream file;
        file.open("output.txt");

        file << "IP Inserido: " << bitsIP;

        int i;
        for (i = 7; i >= 0; i--)
            if (bitsIP[0][i] == 0)
                break;
        
        char classe = 7 - i + 'A';
        file << " (Classe " << classe;
        if (classe == 'A' && bitsIP[0].to_ulong() == 10) {
            file << " - Privado)" << endl;
        } else if (classe == 'B' && bitsIP[0].to_ulong() == 172 && bitsIP[1].to_ulong() >= 16 && bitsIP[1].to_ulong() <= 31) {
            file << " - Privado)" << endl;
        } else if (classe == 'C' && bitsIP[0].to_ulong() == 192 && bitsIP[1].to_ulong() == 168) {
            file << " - Privado)" << endl;
        } else {
            file << " - Publico)" << endl;
        }

        IP bitsNetMask;
        int tamNetMask;
        switch (classe) {
            case 'A':
                bitsNetMask = strToBits("255.0.0.0.");
                tamNetMask = 8;
                break;
                
            case 'B':
                bitsNetMask = strToBits("255.255.0.0.");
                tamNetMask = 16;
                break;
                
            case 'C':
                bitsNetMask = strToBits("255.255.255.0.");
                tamNetMask = 24;
                break;
                
            default:
                file << " - Sem Default Mask";
                exit(0);
        }
            
        string subMask = argv[2];
        subMask += '.';
        
        IP bitsSubMask = strToBits(subMask);

        int tamHost = 0;
        for (auto bits : bitsSubMask)
            for (int i = 7; i >= 0; i--)
                if (bits[i] == 1) {
                    if (tamHost != 0)
                        exit(-1);
                } else
                    tamHost++;

        int tamSubnet = 32 - tamNetMask - tamHost;
        int nSubNet = pow(2, tamSubnet);
        int nHost = pow(2, tamHost);

        file << "Net mask: " << bitsNetMask << " (/" << tamNetMask << ")" << endl;
        file << "Subnet mask: " << bitsSubMask << " (/" << tamSubnet + tamNetMask << ")" << " - Numero de subnets: " << nSubNet << endl;
        file << "HostID: " << tamHost << " bits - IPs uteis por rede: " << nHost - 2 << endl;
        file << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;

        IP IPAtual = bitsIP;

        for (int j = 0; j < 4; j++)
            for (int i = 7; i >= 0; i--)
                IPAtual[j][i] = IPAtual[j][i] & bitsNetMask[j][i];

        int faltam;
        bitset<32> hostBits;
        for (int rede = 0; rede < nSubNet; rede++) {
            file << "Rede " << rede + 1 << endl;
            file << IPAtual << " (IP de Rede)" << endl;

            for (int host = 0; host < nHost; host++) {
                faltam = tamHost;
                hostBits = 0;

                while (faltam != 0) {
                    for (int j = 3; j >= 0; j--) // Percorrer os 4 bytes
                        for (int i = 0; i < 8; i++) // Percorrer cada bit
                            if (faltam == 0) {
                                break;
                            } else {
                                hostBits[tamHost - (faltam--)] = IPAtual[j][i];
                            }

                        if (faltam == 0)
                            break;
                }

                faltam = tamHost;

                if ((hostBits.to_ulong() + 1) == pow(2, tamHost)) {
                    
                    for (int j = 0; j < 4; j++) // Percorrer os 4 bytes
                        for (int i = 7; i >= 0; i--) // Percorrer cada bit
                            hostBits[(j * 8) + i] = IPAtual[3 - j][i];

                    hostBits = hostBits.to_ulong() + 1;

                    file << endl;

                    for (int j = 0; j < 4; j++) // Percorrer os 4 bytes
                        for (int i = 7; i >= 0; i--) // Percorrer cada bit
                            IPAtual[3 - j][i] = hostBits[(j * 8) + i];
                    

                    break;
                } else {
                    hostBits = hostBits.to_ulong() + 1;

                    while (faltam != 0) {
                        for (int j = 3; j >= 0; j--) // Percorrer os 4 bytes
                            for (int i = 0; i < 8; i++) // Percorrer cada bit
                                if (faltam == 0) {
                                    break;
                                } else
                                    IPAtual[j][i] = hostBits[tamHost - (faltam--)];

                            if (faltam == 0)
                                break;
                    }

                    file << IPAtual << ((hostBits.to_ulong() + 1 == pow(2, tamHost)) ? " (IP de Difusao)\n" : "\n");
                }
            }
        }

        file.close();
        return 0;
    }
}
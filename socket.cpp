#include "socket.h"

using namespace std;

//SOCKET作成
void Socket::set_listenfd(){
    //socket(int domain, int type, int protcol)
    //AF_INET == IPv4, SOCK_STREAM == TCP
    
    this->listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //socketが作成されてなければログを出す。
    if(this->listenfd == -1){
        cout << "socket() failed." << endl;
    }
}

//sockaddr_inのインスタンスにパラメータ設定
void Socket::set_sockaddr_in(){
    //初期化
    memset(&this->serv_addr, 0, sizeof(this->serv_addr));
    //通信の種類　AF_INETは　IPv4
    this->serv_addr.sin_family = AF_INET;
    //htonはホストバイトオーダーをネットワークバイトオーダーに変換する　S_addrに指定したネットワークバイトオーダーを設定する。
    this->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //portをネットワークバイトオーダーに変換し保存する。
    this->serv_addr.sin_port = htons(this->port);


}

int Socket::set_socket(){

    Socket::set_listenfd();
    int optval = 1;
    //socketのオプションを設定
    //setsockopt( SOCKET s, int level, int optname, const char* optval, int optlen)
    //第一引数　ソケットのインスタンス、　第二引数　オプションが定義されるレベル、　第三引数　値がセットされることになっているソケットオプション　第四引数　要求されたオプションのための値が指定されるバッファへのポインター。　第五引数　バイト数による、optval バッファのサイズ。
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1){
        cout << "setsockopt() failed." << endl;
        close(this->listenfd);
        return -1;
    }

    Socket::set_sockaddr_in();
    //ソケットの登録 ポート番号などservaddrに代入した値をソケットに割り当てる。
    if(bind(this->listenfd, (struct sockaddr*)&this->serv_addr, sizeof(this->serv_addr)) == -1){
        cout << "bind() failed.(" << errno << ")" << endl;
        close(this->listenfd);
        return -1;
    }

    //bindしたソケットを接続待ちにする。
    if(listen(this->listenfd, SOMAXCONN) == -1){

        cout << "listen() failed." << endl;
        close(this->listenfd);
        return -1;
    }

    return 0;

}


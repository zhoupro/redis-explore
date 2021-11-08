package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	Conn("localhost:6380")

}

func Conn(service string) {

	// 绑定
	tcpAddr, err := net.ResolveTCPAddr("tcp", service)
	checkError(err)
	// 连接
	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	checkError(err)
	//for {
	// 发送
	_, err = conn.Write([]byte("Hello server"))
	checkError(err)
	//}
	conn.Close()
}

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}
}

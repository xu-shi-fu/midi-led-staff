package main

import (
	"fmt"
	"net"
	"time"
)

func run_udp_test() error {

	const network = "udp"
	data := []byte{'h', 'e', 'l', 'l', 'o'}

	addr1, err := net.ResolveUDPAddr(network, ":2333") // local
	if err != nil {
		return err
	}

	addr2, err := net.ResolveUDPAddr(network, "192.168.0.104:2333") // remote
	if err != nil {
		return err
	}

	conn, err := net.ListenUDP(network, addr1)
	if err != nil {
		return err
	}

	defer conn.Close()

	for {

		cb, err := conn.WriteToUDP(data, addr2)

		if err != nil {
			return err
		}

		fmt.Println("send data, cb=", cb)

		time.Sleep(time.Millisecond * 5000)
	}
}

func main() {
	err := run_udp_test()
	if err == nil {
		return
	}
	panic(err)
}

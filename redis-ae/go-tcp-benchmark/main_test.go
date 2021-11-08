package main

import "testing"

func BenchmarkConn(b *testing.B) {
	for n := 0; n < b.N; n++ {
		Conn("localhost:6380")
	}
}

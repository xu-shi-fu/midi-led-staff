package mlscp

// Method 表示一个请求的方法, 它通常是一个 HTTP 方法, 例如 GET, POST, PUT, DELETE 等
type Method uint8

const (

	// MethodGet 表示一个 GET 请求
	MethodGet Method = 1

	// MethodPost 表示一个 POST 请求
	MethodPost Method = 2

	// MethodPut 表示一个 PUT 请求
	MethodPut Method = 3

	// MethodDelete 表示一个 DELETE 请求
	MethodDelete Method = 4
)

func (m Method) UINT() uint8 {
	return uint8(m)
}

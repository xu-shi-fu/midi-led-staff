package vo

// Connections ...
type Connections struct {
	Base

	ServerHost string `json:"server_host"`
	ServerPort int    `json:"server_port"`

	ClientPort int `json:"client_host"`
}

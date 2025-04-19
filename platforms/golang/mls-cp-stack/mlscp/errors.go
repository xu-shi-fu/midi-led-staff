package mlscp

import (
	"fmt"

	"github.com/starter-go/vlog"
)

func HandleError(err error) {
	innerHandleError(err)
}

func HandleErrorX(x any) {
	innerHandleErrorX(x)
}

////////////////////////////////////////////////////////////////////////////////

func innerHandleError(err error) {
	if err == nil {
		return
	}
	vlog.Error("error: %s", err.Error())
}

func innerHandleErrorX(x any) {

	if x == nil {
		return
	}

	err, ok := x.(error)
	if ok {
		innerHandleError(err)
		return
	}

	str, ok := x.(string)
	if ok {
		innerHandleError(fmt.Errorf("error_string: %s", str))
		return
	}

	vlog.Error("error: %v", x)
}

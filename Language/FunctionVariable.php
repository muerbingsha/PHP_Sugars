/* 函数参量可选 / 参量默认值
 * 同swift  func getDefault(type: String, value: Any?, check: Int = 1) */
function getDefault($type, $value = null, $check = 1){
    echo $check;

    if ($type == "int") {
        return $value ?? 0;
    } else if ($type == "str" ) {
        return $value ? $value : "";
    } else if ($type == "bool") {
        return $value ?? false;
    }
}

var_dump(getDefault("int"));
var_dump(getDefault("int", 8));
var_dump(getDefault("bool"));
var_dump(getDefault("bool", true));
var_dump(getDefault("str"));
var_dump(getDefault("str", "good!"));

/* swift version
func getDefault(type: String, value: Any? = nil, check: Int = 1) -> Any? {
        if type == "int" {
              return value ?? 0
         } else if type == "bool" {
              return value ?? false
        } else if type == "str" {
              return value ?? ""
        }
         return nil
    }

print(getDefault(type: "int"))
print(getDefault(type: "int", value: 8, check: 1))
print(getDefault(type: "bool"))
print(getDefault(type: "bool", value: true, check: 1))
print(getDefault(type: "str"))
print(getDefault(type: "str", value: "in swift", check: 1))

*/

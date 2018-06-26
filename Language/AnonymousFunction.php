/* anonymous func */

/* 匿名函数作为变量 - 闭包 
 * swift var a = () -> Void
$greet = function($name){ printf("Hello: %s \n", $name); };
$greet("Shark");


/* 匿名函数使用外部变量 - 复制 *//*
$msg = "hello";
$example = function() use($msg) {
    var_dump($msg);  //hello

    $msg = "world";
    var_dump($msg);  //world
};
$example();
echo $msg;           //hello
*/


/* 匿名函数使用外部变量 - 引用 *//*　
$msg2 = "code";
$example2 = function() use(&$msg2){
    var_dump($msg2);  //code

    $msg2 = "everyday";
    var_dump($msg2);  //everyday
};
$example2();
echo $msg2;   //everyday
*/


/* 匿名函数继承变量 */
class Cart {
    const PRICE_BUTTER = 1.2;  //常量 zend_register_class_constant_long
    const PRICE_MILK = 2.6;
    const PRICE_APPLE = 3.8;

    protected $products = array();

    /* 不需要构造函数 
     * swift: class 必须有init; struct 不强制用户实现，会默认生成init */

    function add($product, $quantity){  //函数参量不需要指明类型，$万能变量zval
        $this->products[$product]=$quantity;
    }

    function getQuantity($product){
        return $this->products[$product] ?? FALSE;  //php 7.1
    }

    function total($tax){
        $total = 0;
        $callback = function($quantity, $product) use($tax, &$total) {
            $pricePerItem = constant(__CLASS__."::PRICE_".strtoupper($product));
            $total += $pricePerItem * $quantity * (1 + $tax);
        };
        array_walk($this->products, $callback); //(value, key)
        return round($total, 2);
    }
}


$myCart = new Cart();
$myCart->add("apple", 3);
$myCart->add("milk", 10);
$myCart->add("butter", 20);


echo $myCart->total(0.25);
?>

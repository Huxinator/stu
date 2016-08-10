<?hh
require_once 'vendor/autoload.php';
require_once 'di.hh';

@session_start();

$server = new \Lx\JsonRpcXp\Server();
$server->registerFactory(
	function() use ($di_container) {
		return new \STU\Core\RPC\External($di_container);
	}, 'external'
);
$server->registerFactory(
	function() use ($di_container) {
		return new \STU\Core\RPC\Maindesk($di_container);
	}, 'maindesk'
);
$server->registerFactory(
	function() use ($di_container) {
		return new \STU\Core\RPC\User($di_container);
	}, 'user'
);
$server->registerFactory(
	function() use ($di_container) {
		return new \STU\Core\RPC\Settings($di_container);
	}, 'settings'
);
$server->registerFactory(
	function() use ($di_container) {
		return new \STU\Core\RPC\Shiplist($di_container);
	}, 'shiplist'
);
$server->registerFactory(
	function() use ($di_container) {
		return new \STU\Core\RPC\Planetlist($di_container);
	}, 'planetlist'
);
$server->registerFactory(
	function() use ($di_container) {
		return new \STU\Core\RPC\Ship($di_container, $di_container->ship_component_factory);
	}, 'ship'
);
header('Access-Control-Allow-Origin: *');

$transport = new \Lx\JsonRpcXp\Transport\Http();
$transport->handle($server);

<?hh
namespace STU\DI;

class DIContainer extends \Pimple\Container {

	public function __get(string $key): mixed {
		if ($this->offsetExists($key)) {
			return $this->offsetGet($key);
		}
		throw new \Exception('Service '.$key.' not found in DIContainer');
	}
}

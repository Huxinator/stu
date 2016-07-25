<?hh
namespace STU\Session;

use \STU\Exception\ArrayKeyNotFound;

class Storage {

	public function hasKey(string $key): bool {
		return array_key_exists($key, $_SESSION);
	}

	public function getKey(string $key): mixed {
		if (!$this->hasKey($key)) {
			return false;
		}
		return $_SESSION[$key];
	}

	public function setKey(string $key, mixed $value): void {
		$_SESSION[$key] = $value;
	}

	public function delKey(string $key): void {
		unset($_SESSION[$key]);
	}
}

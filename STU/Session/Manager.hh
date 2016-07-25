<?hh
namespace STU\Session;

use \STU\DI\DIContainer;
use \STU\Model\UserTableInterface;

class Manager {
	
	private DIContainer $di_container;

	private ?UserTableInterface $current_user;

	public function __construct(DIContainer $di_container): void {
		$this->di_container = $di_container;
	}

	public function initForUser(UserTableInterface $user): void {
		$this->updateForUser($user);
	}

	public function updateForUser(UserTableInterface $user): void {
		$storage = $this->di_container->session_storage;

		$storage->setKey('valid', true);
		$storage->setKey('user_id', $user->getId());
		$storage->setKey('user_name', $user->getName());
	}

	public function getUserId(): int {
		$storage = $this->di_container->session_storage;

		if (!$storage->hasKey('user_id')) {
			throw new \Exception('user_id missing in session');
		}
		return (int) $storage->getKey('user_id');
	}

	public function isValid(): bool {
		return $this->di_container->session_storage->hasKey('valid');
	}

	public function getCurrentUser(): UserTableInterface {
		if ($this->current_user === null) {
			if (!$this->isValid()) {
				throw new \Exception('Session invalid');
			}
			$this->current_user = $this->di_container->user->getById($this->getUserId());
		}
		return $this->current_user;
	}
}

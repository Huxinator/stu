<?hh
namespace STU\Core\RPC;

use Lx\JsonRpcXp\Fault;
use Monolog\Logger;
use STU\DI\DIContainer;

abstract class Base {

	const int ERROR_NO_LOGIN = -42;

	const int ERROR_DEFAULT = -666;
	
	const int OBJECT_NOT_FOUND = 1;

	private DIContainer $di_container;

	public function __construct(DIContainer $di_container): void {
		$this->di_container = $di_container;
	}

	protected function logDebug(string $message): void {
		$this->getDIContainer()->logger->addDebug($message);
	}

	protected function logError(string $message): void {
		$this->getDIContainer()->logger->addCritical($message);
	}

	protected function fault(string $message, int $errorcode): void {
		throw new Fault($message, $errorcode);
	}

	protected function getDIContainer(): DIContainer {
		return $this->di_container;
	}

	protected function getSessionManager(): \STU\Session\Manager {
		return $this->getDIContainer()->session_manager;
	}

}

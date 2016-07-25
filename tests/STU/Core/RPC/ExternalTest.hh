<?hh
namespace Test\STU\Core\RPC;

use \Mockery;

class ExternalText extends \PHPUnit_Framework_TestCase {

	private $controller;

	private $di_container;

	private $session_manager;

	private $user;

	private $user_query;

	public function setUp() {
		$this->di_container = Mockery::mock(\STU\DI\DIContainer::class);
		
		$this->user = Mockery::mock(\STU\Model\UserTableInterface::class);

		$this->session_manager = Mockery::mock(\STU\Session\Manager::class);
		
		$this->di_container->session_manager = $this->session_manager;
		$this->di_container->user = $this->user;

		$this->controller = new \STU\Core\RPC\External($this->di_container);
	}

	/**
	 * @expectedException \Lx\JsonRpcXp\Fault
	 * @expectedExceptionCode -42
	 */
	public function testLoginFailsOnWrongCredentials() {
		$email = 'roedl@broem.de';

		$this->user
			->shouldReceive('findObject')
			->once()
			->with('email=\''.$email.'\'')
			->andReturn(false);

		$this->controller->login($email, 'roedl');
	}

	public function testLoginReturnsArrayWithUserData() {
		$user_name = 'username';
		$user = Mockery::mock(\STU\Model\UserTableInterface::class);
		$user->shouldReceive('getName')
			->once()
			->andReturn($user_name);
		$this->user
			->shouldReceive('findObject')
			->once()
			->andReturn($user);
		
		$this->session_manager->shouldReceive('initForUser')->with($user)->once();

		$this->assertSame(
			['username' => $user_name, 'faction_id' => 1],
			$this->controller->login('roedl', 'broem')
		);
	}

	public function testHasValidSessionReturnsBoolean() {
		$this->session_manager->shouldReceive('isValid')->once()->andReturn(true);

		$this->assertInternalType(
			'bool',
			$this->controller->hasValidSession()
		);
	}
}

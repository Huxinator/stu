<?hh
namespace Test\STU\Session;

use \Mockery;

class ManagerTest extends \PHPUnit_Framework_TestCase {

	private $manager;

	private $di_container;

	private $session_storage;

	public function setUp() {
		$this->di_container = Mockery::mock(\STU\DI\DIContainer::class);

		$this->session_storage = Mockery::mock(\STU\Session\Storage::class);

		$this->di_container->session_storage = $this->session_storage;

		$this->manager = new \STU\Session\Manager($this->di_container);
	}

	public function testInitForUserUpdatesStorage() {
		$user_id = 1234;
		$user_name = 'name';

		$this->session_storage->shouldReceive('setKey')->with('valid', true);
		$this->session_storage->shouldReceive('setKey')->with('user_id', $user_id);
		$this->session_storage->shouldReceive('setKey')->with('user_name', $user_name);
		
		$user = Mockery::mock(\STU\Model\UserTableInterface::class);
		$user->shouldReceive('getId')
			->once()
			->andReturn($user_id);
		$user->shouldReceive('getName')
			->once()
			->andReturn($user_name);

		$this->manager->initForUser($user);
	}

	/**
	 * @expectedException \Exception
	 * @expectedExceptionMessage user_id missing in session
	 */
	public function testGetUserIdFailsIfIdIsMissing() {
		$this->session_storage->shouldReceive('hasKey')->once()->andReturn(false);

		$this->manager->getUserId();
	}

	public function testGetUserIdReturnsIdFromStorage() {
		$this->session_storage->shouldReceive('hasKey')->with('user_id')->once()->andReturn(true);

		$user_id = 666;
		
		$this->session_storage->shouldReceive('getKey')->with('user_id')->once()->andReturn($user_id);

		$this->assertEquals(
			$user_id,
			$this->manager->getUserId()
		);
	}

	public function testIsValidReturnsBoolFromStorage() {
		$this->session_storage->shouldReceive('hasKey')->with('valid')->once()->andReturn(true);
		
		$this->assertInternalType(
			'bool',
			$this->manager->isValid()
		);
	}

	/**
	 * @expectedException \Exception
	 * @expectedExpectionMessage Session invalid
	 */
	public function testGetCurrentUserFailsOnInvalidSession() {
		$this->session_storage->shouldReceive('hasKey')->with('valid')->once()->andReturn(false);

		$this->manager->getCurrentUser();
	}

	public function getGetCurrentUserReturnsUserTableInterface() {
		$user_id = 666;
		$this->session_storage->shouldReceive('hasKey')->with('valid')->once()->andReturn(true);
		$this->session_storage->shouldReceive('hasKey')->with('user_id')->once()->andReturn(true);
		$this->session_storage->shouldReceive('getKey')->with('user_id')->once()->andReturn($user_id);

		$user_query = $this->getMock(\STU\Model\UserTableInterface::class);
		$user_query->expects($this->once())
			->method('getById')
			->with($this->equalTo($user_id))
			->willReturn($this->getMock(\STU\Model\UserTableInterface::class));

		$this->assertInstanceOf(
			'\STU\Model\UserTableInterface',
			$this->manager->getCurrentUser()
		);
	}
}

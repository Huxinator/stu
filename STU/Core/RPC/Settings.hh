<?hh
namespace STU\Core\RPC;

class Settings extends Base {

	public function updateUserName(string $new_username): bool {
		$current_user = $this->getSessionManager()->getCurrentUser();

		$current_user->setName($new_username);
		$current_user->save();

		$this->getDIContainer()->session_manager->updateForUser($current_user);

		return true;
	}
}

<?hh
namespace STU\Core\RPC;

class User extends Base {

	public function getData(): array<string, mixed> {
		$current_user = $this->getSessionManager()->getCurrentUser();

		$data = array(
			'username' => $current_user->getName(),
			'faction_id' => $current_user->getFactionId(),
			'email' => $current_user->getEmail()
		);

		return $data;
	}

}

<?hh
namespace STU\Core\RPC;

use STU\Model as Model;

class External extends Base {

	const STATE_PENDING = 1;

	public function login(string $email, string $password): array {
		$user = $this->getDIContainer()->user->findObject('email=\''.$email.'\'');

		if (!$user) {
			$this->fault('Die Benutzerdaten sind ungültig', self::ERROR_NO_LOGIN);
		}

		$this->getSessionManager()->initForUser($user);

		$data = [
			'username' => $user->getName(),
			'faction_id' => 1
		];
		return $data;
	}
	
	public function getFactionList(): array {
		$factions = [];
		$factions[1] = [
			'id' => 1,
			'name' => 'Vereinte Föderation der Planeten'
		];
		$factions[2] = [
			'id' => 2,
			'name' => 'Romulanisches Imperium'
		];
		return array('factions' => $factions);
	}

	public function register(string $email, int $faction_id): string {
		$this->checkEmail($email);
		if (!isset($this->getFactionList()['factions'][$faction_id])) {
			$this->fault('Fraktion nicht vorhanden', self::ERROR_DEFAULT);
		}
		//$password = password_hash(\STU\Core\Helper\PasswordGenerator::generate(), PASSWORD_DEFAULT);
		$password = password_hash('zomglol', PASSWORD_DEFAULT);
		if ($password === null) {
			$this->fault('Password generation failed', self::ERROR_DEFAULT);
			return '';
		}

		// XXX The user is supposed to be activated by a verification 
		// email as well as he has to change his password within the 
		// verification. Use the default password 'zomglol' for now
		$user = $this->getDIContainer()->user;
		$user->setEmail($email);
		$user->setPassword($password);
		$user->setState(static::STATE_PENDING);
		$user->setFactionId($faction_id);
		$user->setName('Spieler');
		$user->save();

		$this->sendRegistrationMail($user);

		return 'Registrierung erfolgreich, bitte befolge die Anweisungen in der eMail die wir Dir soeben geschickt haben';
	}
	
	public function checkEmail(string $email): string {
		$validator = new \Zend\Validator\EmailAddress();
		if (!$validator->isValid($email)) {
			$this->fault('Die eMail-Adresse ist ungültig', self::ERROR_DEFAULT);
		}	

		$user = Model\UserQuery::getByEmailAddress($email);
		if ($user) {
			$this->fault('Die eMail-Adresse wird bereits genutzt', self::ERROR_DEFAULT);
		}

		return 'Die eMail-Adresse ist verwendbar';
	}

	public function hasValidSession(): bool {
		return $this->getSessionManager()->isValid();
	}

	private function sendRegistrationMail(Model\User $user): void {
		$mail = new \Zend\Mail\Message();
		$mail->setBody('This is the text of the email.');
		$mail->setFrom('sometrek@example.com', 'Some Trek Universe');
		$mail->addTo($user->getEmail(), 'Spieler');
		$mail->setSubject('Deine Registrierung bei Some Trek Universe');

		$transport = new \Zend\Mail\Transport\Sendmail();
		$transport->send($mail);
	}

}

<?hh // strict
namespace STU\Core\Type;

use STU\Model\UserTableInterface;

/**
 * Class: ForeignUser
 *
 * @see \JsonSerializable
 * @final
 *
 * Like ForeignShip, ForeignUser provides just public informations about a
 * user
 */
final class ForeignUser implements ForeignUserInterface {

	public function __construct(private UserTableInterface $user): void {
	}

	public function jsonSerialize(): array<string, mixed> {
		return [
			'id' => $this->user->getId(),
			'name' => $this->user->getName()
		];	
	}
}

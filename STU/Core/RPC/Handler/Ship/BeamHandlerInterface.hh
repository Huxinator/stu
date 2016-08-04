<?hh // strict
namespace STU\Core\RPC\Handler\Ship;

use STU\Model\ShipTableInterface;

interface BeamHandlerInterface {

	public function beam(ShipTableInterface $ship, ShipTableInterface $foreign_ship, array<int,\stdClass> $commodity_list): array<int,int>;
}

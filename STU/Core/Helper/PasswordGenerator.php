<?php
namespace STU\Core\Helper;

class PasswordGenerator { #{{{

	/**
	 * @return string
	 */
	public function generate() { #{{{
		$dummy = array_merge(range('0', '9'), range('a', 'z'), range('A', 'Z'), array('#','&','@','$','_','%','?','+'));
		mt_srand((double)microtime()*1000000);
		for ($i = 1; $i <= (count($dummy)*2); $i++) {
			$swap = mt_rand(0,count($dummy)-1);
			$tmp = $dummy[$swap];
			$dummy[$swap] = $dummy[0];
			$dummy[0] = $tmp;
		}
		return substr(implode('',$dummy),0,$length);
	} # }}}

	
} #}}}

<?php
/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

/**
 * PHP implementation of XXTEA encryption algorithm.
 *
 * XXTEA is a secure and fast encryption algorithm, suitable for web
 * development.
 *
 * PHP versions 4 and 5
 *
 * LICENSE: This library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 *
 * @category   Encryption
 * @package    Crypt_XXTEA
 * @author     Wudi Liu <wudicgi@gmail.com>
 * @author     Ma Bingyao <andot@ujn.edu.cn>
 * @copyright  2005-2008 Coolcode.CN
 * @license    http://www.gnu.org/copyleft/lesser.html  LGPL License 2.1
 * @version    CVS: $Id: XXTEA.php,v 1.3 2008/03/06 11:38:45 wudicgi Exp $
 * @link       http://pear.php.net/package/Crypt_XXTEA
 */

// {{{ constants

define('CRYPT_XXTEA_DELTA', 0x9E3779B9);

// }}}

/**
 * The main class
 *
 * @category   Encryption
 * @package    Crypt_XXTEA
 * @author     Wudi Liu <wudicgi@gmail.com>
 * @author     Ma Bingyao <andot@ujn.edu.cn>
 * @copyright  2005-2008 Coolcode.CN
 * @license    http://www.gnu.org/copyleft/lesser.html  LGPL License 2.1
 * @version    Release: 0.9.0
 * @link       http://pear.php.net/package/Crypt_XXTEA
 */
class XXTEA {
    // {{{ properties

    /**
     * The long integer array of secret key
     *
     * @access private
     *
     * @var array
     */
    var $_key;

    // }}}

    // {{{ setKey()

    /**
     * Sets the secret key
     *
     * The key must be non-empty, and not more than 16 characters or 4 long values
     *
     * @access public
     *
     * @param mixed $key  the secret key (string or long integer array)
     *
     * @return bool  true on success, PEAR_Error on failure
     */
    function setKey($key) {
        if (is_string($key)) {
            $k = $this->_str2long($key, false);
        } elseif (is_array($key)) {
            $k = $key;
        } else {
            throw new Exception('The secret key must be a string or long integer array.');
        }
        if (count($k) > 4) {
            throw new Exception('The secret key cannot be more than 16 characters or 4 long values.');
        } elseif (count($k) == 0) {
            throw new Exception('The secret key cannot be empty.');
        } elseif (count($k) < 4) {
            for ($i = count($k); $i < 4; $i++) {
                $k[$i] = 0;
            }
        }
        $this->_key = $k;
        return true;
    }

    // }}}

    // {{{ encrypt()

    /**
     * Encrypts a plain text
     *
     * As the XXTEA encryption algorithm is designed for encrypting and decrypting
     * the long integer array type of data, there is not a standard that defines
     * how to convert between long integer array and text or binary data for it.
     * So this package provides the ability to encrypt and decrypt the long integer
     * arrays directly to satisfy the requirement for working with other
     * implementations. And at the same time, for convenience, it also provides
     * the ability to process strings, which uses its own method to group the text
     * into array.
     *
     * @access public
     *
     * @param mixed $plaintext  the plain text (string or long integer array)
     *
     * @return mixed  the cipher text as the same type as the parameter $plaintext
     *                 on success, PEAR_Error on failure
     */
    function encrypt($plaintext) {
        if ($this->_key == null) {
            throw new Exception('Secret key is undefined.');
        }
        if (is_string($plaintext)) {
            return $this->_encryptString($plaintext);
        } elseif (is_array($plaintext)) {
            return $this->_encryptArray($plaintext);
        } else {
            throw new Exception('The plain text must be a string or long integer array.');
        }
    }

    // }}}

    // {{{ decrypt()

    /**
     * Decrypts a cipher text
     *
     * @access public
     *
     * @param mixed $chipertext  the cipher text (string or long integer array)
     *
     * @return mixed  the plain text as the same type as the parameter $chipertext
     *                 on success, PEAR_Error on failure
     */
    function decrypt($chipertext) {
        if ($this->_key == null) {
            throw new Exception('Secret key is undefined.');
        }
        if (is_string($chipertext)) {
            return $this->_decryptString($chipertext);
        } elseif (is_array($chipertext)) {
            return $this->_decryptArray($chipertext);
        } else {
            throw new Exception('The chiper text must be a string or long integer array.');
        }
    }

    // }}}

    // {{{ _encryptString()

    /**
     * Encrypts a string
     *
     * @access private
     *
     * @param string $str  the string to encrypt
     *
     * @return string  the string type of the cipher text on success,
     *                  PEAR_Error on failure
     */
    function _encryptString($str) {
        if ($str == '') {
            return '';
        }
        $v = $this->_str2long($str, true);
        $v = $this->_encryptArray($v);
        return $this->_long2str($v, false);
    }

    // }}}

    // {{{ _encryptArray()

    /**
     * Encrypts a long integer array
     *
     * @access private
     *
     * @param array $v  the long integer array to encrypt
     *
     * @return array  the array type of the cipher text on success,
     *                 PEAR_Error on failure
     */
    function _encryptArray($v) {
        $n = count($v) - 1;
        $z = $v[$n];
        $y = $v[0];
        $q = floor(6 + 52 / ($n + 1));
        $sum = 0;
        while (0 < $q--) {
            $sum = $this->_int32($sum + CRYPT_XXTEA_DELTA);
            $e = $sum >> 2 & 3;
            for ($p = 0; $p < $n; $p++) {
                $y = $v[$p + 1];
                $mx = $this->_int32((($z >> 5 & 0x07FFFFFF) ^ $y << 2) + (($y >> 3 & 0x1FFFFFFF) ^ $z << 4)) ^ $this->_int32(($sum ^ $y) + ($this->_key[$p & 3 ^ $e] ^ $z));
                $z = $v[$p] = $this->_int32($v[$p] + $mx);
            }
            $y = $v[0];
            $mx = $this->_int32((($z >> 5 & 0x07FFFFFF) ^ $y << 2) + (($y >> 3 & 0x1FFFFFFF) ^ $z << 4)) ^ $this->_int32(($sum ^ $y) + ($this->_key[$p & 3 ^ $e] ^ $z));
            $z = $v[$n] = $this->_int32($v[$n] + $mx);
        }
        return $v;
    }

    // }}}

    // {{{ _decryptString()

    /**
     * Decrypts a string
     *
     * @access private
     *
     * @param string $str  the string to decrypt
     *
     * @return string  the string type of the plain text on success,
     *                  PEAR_Error on failure
     */
    function _decryptString($str) {
        if ($str == '') {
            return '';
        }
        $v = $this->_str2long($str, false);
        $v = $this->_decryptArray($v);
        return $this->_long2str($v, true);
    }

    // }}}

    // {{{ _encryptArray()

    /**
     * Decrypts a long integer array
     *
     * @access private
     *
     * @param array $v  the long integer array to decrypt
     *
     * @return array  the array type of the plain text on success,
     *                 PEAR_Error on failure
     */
    function _decryptArray($v) {
        $n = count($v) - 1;
        $z = $v[$n];
        $y = $v[0];
        $q = floor(6 + 52 / ($n + 1));
        $sum = $this->_int32($q * CRYPT_XXTEA_DELTA);
        while ($sum != 0) {
            $e = $sum >> 2 & 3;
            for ($p = $n; $p > 0; $p--) {
                $z = $v[$p - 1];
                $mx = $this->_int32((($z >> 5 & 0x07FFFFFF) ^ $y << 2) + (($y >> 3 & 0x1FFFFFFF) ^ $z << 4)) ^ $this->_int32(($sum ^ $y) + ($this->_key[$p & 3 ^ $e] ^ $z));
                $y = $v[$p] = $this->_int32($v[$p] - $mx);
            }
            $z = $v[$n];
            $mx = $this->_int32((($z >> 5 & 0x07FFFFFF) ^ $y << 2) + (($y >> 3 & 0x1FFFFFFF) ^ $z << 4)) ^ $this->_int32(($sum ^ $y) + ($this->_key[$p & 3 ^ $e] ^ $z));
            $y = $v[0] = $this->_int32($v[0] - $mx);
            $sum = $this->_int32($sum - CRYPT_XXTEA_DELTA);
        }
        return $v;
    }

    // }}}

    // {{{ _long2str()

    /**
     * Converts long integer array to string
     *
     * @access private
     *
     * @param array $v  the long integer array
     * @param bool  $w  whether the given array contains the length of
     *                   original plain text
     *
     * @return string  the string
     */
    function _long2str($v, $w) {
        $len = count($v);
        $s = '';
        for ($i = 0; $i < $len; $i++) {
            $s .= pack('V', $v[$i]);
        }
        if ($w) {
            return substr($s, 0, $v[$len - 1]);
        } else {
            return $s;
        }
    }

    // }}}

    // {{{ _str2long()

    /**
     * Converts string to long integer array
     *
     * @access private
     *
     * @param string $s  the string
     * @param bool   $w  whether to append the length of string to array
     *
     * @return string  the long integer array
     */
    function _str2long($s, $w) {
        $v = array_values(unpack('V*', $s.str_repeat("\0", (4-strlen($s)%4)&3)));
        if ($w) {
            $v[] = strlen($s);
        }
        return $v;
    }

    // }}}

    // {{{ _int32()

    /**
     * Corrects long integer value
     *
     * Because a number beyond the bounds of the integer type will be automatically
     * interpreted as a float, the simulation of integer overflow is needed.
     *
     * @access private
     *
     * @param int $n  the integer
     *
     * @return int  the correct integer
     */
    function _int32($n) {
        while ($n >= 2147483648) $n -= 4294967296;
        while ($n <= -2147483649) $n += 4294967296;
        return (int)$n;
    }

    // }}}

}

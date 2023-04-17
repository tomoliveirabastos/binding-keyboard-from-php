<?php

$ffi = FFI::cdef("void run(void (*function)(int n));", __DIR__ . "/lib.dll");
$ffi->run(function($data) {

    var_dump($data);
});
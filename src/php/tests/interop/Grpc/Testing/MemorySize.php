<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# NO CHECKED-IN PROTOBUF GENCODE
# source: src/proto/grpc/testing/messages.proto

namespace Grpc\Testing;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

/**
 * Generated from protobuf message <code>grpc.testing.MemorySize</code>
 */
class MemorySize extends \Google\Protobuf\Internal\Message
{
    /**
     * Generated from protobuf field <code>int64 rss = 1;</code>
     */
    protected $rss = 0;

    /**
     * Constructor.
     *
     * @param array $data {
     *     Optional. Data for populating the Message object.
     *
     *     @type int|string $rss
     * }
     */
    public function __construct($data = NULL) {
        \GPBMetadata\Src\Proto\Grpc\Testing\Messages::initOnce();
        parent::__construct($data);
    }

    /**
     * Generated from protobuf field <code>int64 rss = 1;</code>
     * @return int|string
     */
    public function getRss()
    {
        return $this->rss;
    }

    /**
     * Generated from protobuf field <code>int64 rss = 1;</code>
     * @param int|string $var
     * @return $this
     */
    public function setRss($var)
    {
        GPBUtil::checkInt64($var);
        $this->rss = $var;

        return $this;
    }

}


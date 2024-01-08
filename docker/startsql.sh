#!/bin/bash

docker run -ti -d --blkio-weight 100 -v /opt/mysql:/var/lib/mysql -e MYSQL_ROOT_PASSWORD=123456 mysql

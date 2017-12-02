#!/bin/bash

HADOOP_JAR_HOME='$HADOOP_HOME/share/hadoop';

#hadoop common
COMMON_JAR=`ls $HADOOP_JAR_HOME/common/*.jar`

for JAR in $COMMON_JAR
do
        export CLASSPATH=$CLASSPATH:$JAR;
done

#hadoop common lib
COMMON_LIB_JAR=`ls $HADOOP_JAR_HOME/common/lib/*.jar`

for JAR in $COMMON_LIB_JAR
do
        export CLASSPATH=$CLASSPATH:$JAR;
done

#hadoop hdfs
HDFS_JAR=`ls $HADOOP_JAR_HOME/hdfs/*.jar`

for JAR in $HDFS_JAR
do
        export CLASSPATH=$CLASSPATH:$JAR;
done

#hadoop hdfs lib
HDFS_LIB_JAR=`ls $HADOOP_JAR_HOME/hdfs/lib/*.jar`

for JAR in $HDFS_LIB_JAR
do
        export CLASSPATH=$CLASSPATH:$JAR;
done

export LD_LIBRARY_PATH=$JAVA_HOME/jre/lib/i386/server

./hdfstest /test.dat 1111 1111

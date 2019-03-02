#!/bin/sh

BuildSystemExec="premake5"
BuildScriptFile="Build.lua"
ProjectType="xcode"

set echo off

if [ $# -gt 0 ]
then
	BuildSystemExec=$1
fi

if [ -f $BuildSystemExec ]
then
	eval $BuildSystemExec --file=$BuildScriptFile $ProjectType $*
else
	echo "failed to locate the build system executable: $BuildSystemExec"
fi


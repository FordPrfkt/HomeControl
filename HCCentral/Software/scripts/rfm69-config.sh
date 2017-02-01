# get RFM69 count and usage

. scripts/osdefaults.sh

get_rfm69_count() {
  RFM69S=$(echo "#include <avr/io.h>" | avr-gcc -mmcu=$MCU -E -dD - |\
    ${AWK} "BEGIN {numrfm69=0};\
     /.* UDR[0-9]* .*\$/ { num=substr(\$2, 4);\
     num++;\
     if ( num > numrfm69 ) { numrfm69=num } };\
     END { print numrfm69 }")
}

rfm69_choice() {
  i=0
  while [ $i -lt $RFM69S ]; do
    echo "$i  $1_RFM69_$i"
    i=$(( $i + 1))
  done
}

rfm69_process_choice() {
  i=0
  while [ $i -lt $RFM69S ]; do
  	this_rfm69=$(eval "echo \$${1}_RFM69_${i}")
    if [ "$this_rfm69" = y ]; then
      define_symbol "$1_USE_RFM69" $i
      break
    fi
    i=$(( $i + 1))
  done
}

rfm69_count_used() {
  RFM69S_USED=0

  if [ "$RFM69_866_SUPPORT" = y ]; then
    RFM69S_USED=$(($RFM69S_USED + 1))
  fi
  if [ "$RFM69_433_SUPPORT" = y ]; then
    RFM69S_USED=$(($RFM69S_USED + 1))
  fi
}

get_rfm69_count
rfm69_count_used

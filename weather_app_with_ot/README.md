# Demostration of libOTe

- Build with `docker build -t weather_ot_test -f Dockerfile .`
- Run by
    1. `docker run --rm -it weather_ot_test`
    2. `/src/libOTe/bin/weather_ot_server &` to setup the server
    3. `/src/libOTe/bin/weather_ot_user 0` to choose the first temperature and `/src/libOTe/bin/weather_ot_user 1` to
       choose the second temperature.


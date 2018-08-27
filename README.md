# GPS NMEA 0183 Parser

Platform independent GPS NMEA parser for embedded systems

## Features

- Platform independent, easy to port
- Written in ANSI C language
- Parser has built-in support for `4` GPS statements
	- `GPGGA`: GPS fix data
	- `GPGSA`: GPS active satellites and dillusion of position
	- `GPGSV`: List of satellites in view zone
	- `GPRMC`: Recommended minimum specific GPS/Transit data
- Low-level layer is separated from application layer, thus allows you to add custom communication with GPS device
- Works with operating systems
- User friendly MIT license

## Examples and resources

For examples, please check second repository, available at https://github.com/MaJerle/GPS_NMEA_Parser_res

## Documentation

Full API documentation with description and examples is available and is regulary updated with the source changes

http://majerle.eu/documentation/gps/html/index.html

## Contribution

I invite you to give feature request or report a bug. Please use issues tracker.

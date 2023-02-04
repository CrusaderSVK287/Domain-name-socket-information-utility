# Domain-name-socket-information-utility
Simple tool for getting socket information of a domain name.
This tool will print out information about available sockets
on the server of the given domain name. This domain name can
be inputed as a part of a link, like https://example.org, or
just simply example.org. These sockets can then be used when
creating web clients using the UNIX socket api (bind, connect)
or just a quick way to get an ip address of a host

There are four informations this tool provides
* Address        - IP address for example
* Address family - IPv4, IPv6, UNIX, etc.
* Protocol used  - TCP, UDP, etc.
* Socket type    - Stream, datagram, raw, etc.

## Filters
Most common types of aforementioned informations are able to
be filtered away so you only get shown what you need.
For example if you only want sockets that have IPv4 address
bind to them, you specify `-4` or `--ipv4` flag and you will
be shown only sockets implementing this ip version. This filter
only works for the most common types of sockets. In case of
transport protocol used, these are TCP, UDP and Unspecified (any)
protocols. Other, less common, protocols would show allways.

## Usage
To use this program, all you need to do is to specify domain
names you want to get information of in the cli arguments
like this
`./dninfo google.com example.org ...`
and you will get information in this format:
> --------------------------------------------------
>                    google.com
> --------------------------------------------------
> Address:              142.251.36.110
> Address family:    2  IPv4
> Protocol:          6  TCP
> Type:              1  Stream socket
> 
> Address:              142.251.36.110
> Address family:    2  IPv4
> Protocol:         17  UDP
> Type:              2  Datagram socket
> ......

If this is too noisy for you, you can specify the `-c` or
`--compact` flag to get a more *compact* output

>         Address                                 AF    Protocol     Type
> --------------------------------------------------------------------------------
> google.com:
>         142.251.36.110                          IPv4  TCP          Stream socket
>         142.251.36.110                          IPv4  UDP          Datagram sock
>         142.251.36.110                          IPv4  Unspecified  Raw socket   
>         2a00:1450:4014:80b::200e                IPv6  TCP          Stream socket
>         2a00:1450:4014:80b::200e                IPv6  UDP          Datagram sock
>         2a00:1450:4014:80b::200e                IPv6  Unspecified  Raw socket   

Use `./dminfo --help` to see help page and list of all flags
Use `./dminfo --version` to see the current version of the application

# Compilation

1. Clone this repository eighter with https or ssh
HTTPS: `git clone https://github.com/CrusaderSVK287/Domain-name-information-utility.git`
SSH: `git clone git@github.com:CrusaderSVK287/Domain-name-information-utility.git`

2. cd into cloned repository and run `make`

3. Done. Your compiled binary should be in the `bin` folder

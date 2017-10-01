        .global get_tls
get_tls:
        mrs x0, tpidrro_el0
        ret
        

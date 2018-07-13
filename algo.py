def scheduler():
    return

    pumps = STATE['pumps']
    active = [p for p in pumps if p['active']]
    capacity = int(STATE['available_power'] / STATE['pump_startup_watts'])
    running_capacity = int(STATE['available_power'] / STATE['pump_watts'])

    # Activate pump switches
    queued = [p for p in pumps if not p['active'] and p['queued']]
    if queued and len(active) < capacity:
        pump = queued[0]
        pump['active'] = True
        switch_pump(pump['id'], True)

    # Shut down a pump if we don't have enough power
    if active and len(active) > running_capacity:
        pump = active[-1]
        pump['active'] = False
        switch_pump(pump['id'], False)

    # Shut down pumps that have been removed from the queue
    for pump in pumps:
        if pump['active'] and not pump['queued']:
            pump['active'] = False
            switch_pump(pump['id'], False)

    # Reduce time remaining
    for pump in active:
        pump['time_remaining'] = max(pump['time_remaining'] - STATE['check_interval'], 0)

    # Remove pumps from queue
    finished = [p for p in active if p['time_remaining'] == 0]
    for pump in finished:
        pump['active'] = False
        pump['queued'] = False
        switch_pump(pump['id'], False)

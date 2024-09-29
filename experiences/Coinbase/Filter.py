import pprint

# Assume sorted by id
def filter(data, filters, per_page=2, start_at=None):
    pprint.pprint(filters)

    # Start at the beginning
    if start_at is None:
        start_at = 0

    # Return response
    rv = {
        "metadata": {
            "start_at": start_at,
            "per_page": per_page,
            "next": True,
        },
        "data": data,
    }

    # Extract time range
    start_time = filters.pop("start_time")
    end_time = filters.pop("end_time")

    filtered = []
    for idx in range(start_at, len(data)):
        # Stop when we have enough data
        if len(filtered) == per_page:
            start_at = idx
            break

        d = data[idx]

        # First check time
        if start_time <= d["time"] <= end_time:
            # Then check all other filters
            if all(d.get(k) == v for k, v in filters.items()):
                filtered.append(d)

    # Save for future requests
    if idx == len(data) - 1 or len(filtered) < per_page:
        rv["metadata"]["next"] = False
    else:
        rv["metadata"]["start_at"] = start_at

    rv["data"] = filtered

    return rv

def get_filters():
    return dict(start_time=1, end_time=11, user_id=1, currency=2)

def test(data):
    """Filter & get all pages!"""
    # Setup the request
    per_page = 2
    start_at = 0

    # Get first page
    page = filter(data, get_filters(), per_page, start_at)
    pprint.pprint(page)
    print("------")

    i = 0

    while page["metadata"]["next"]:
        start_at = page["metadata"]["start_at"]
        page = filter(data, get_filters(), per_page, start_at)
        pprint.pprint(page)
        print("------")

        i += 1
        if i > 10:
            break

# -----------------

data = [
    {"time": 1, "id": 11, "user_id": 1, "currency": 1, "amount": 10},
    {"time": 2, "id": 12, "user_id": 1, "currency": 3, "amount": 11},
    {"time": 3, "id": 13, "user_id": 2, "currency": 1, "amount": -10},
    {"time": 4, "id": 14, "user_id": 1, "currency": 2, "amount": 12},
    {"time": 5, "id": 5, "user_id": 1, "currency": 2, "amount": -10},
    {"time": 6, "id": 6, "user_id": 1, "currency": 1, "amount": 13},
    {"time": 7, "id": 7, "user_id": 1, "currency": 2, "amount": -5},
    {"time": 8, "id": 8, "user_id": 1, "currency": 2, "amount": 10},
    {"time": 9, "id": 9, "user_id": 1, "currency": 1, "amount": 10},
    {"time": 10, "id": 10, "user_id": 1, "currency": 1, "amount": 15},
    {"time": 10, "id": 21, "user_id": 1, "currency": 1, "amount": 16},
    {"time": 11, "id": 22, "user_id": 1, "currency": 2, "amount": -3},
    {"time": 11, "id": 23, "user_id": 1, "currency": 1, "amount": 5},
    {"time": 12, "id": 24, "user_id": 1, "currency": 2, "amount": 6},
    {"time": 13, "id": 25, "user_id": 1, "currency": 1, "amount": 10}
]

test(data)

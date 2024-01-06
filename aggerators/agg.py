import time
from collections import defaultdict
import pandas as pd
import array


def aggregate():
    data = defaultdict(lambda: {'min': float('+inf'), 'max': float('-inf'), 'sum': 0, 'count': 0})
    # data = defaultdict(lambda: [array.array('f', [float('+inf'), float('-inf'), 0]), array.array('i', [0])])
    data_get = data.__getitem__
    
    with open('../measurements.txt', 'r', buffering=1000000) as f:
        for line in f:
            if not line.strip():
                continue
            name, temperature = line.split(';')
            temperature = float(temperature)
            city = data_get(name)
            # city = data[name]

            city['min'] = min(city['min'], temperature)
            city['max'] = max(city['max'], temperature)
            city['sum'] += temperature
            city['count'] += 1
            # city[0][0] = min(city[0][0], temperature)
            # city[0][1] = max(city[0][1], temperature)
            # city[0][2] += temperature
            # city[1][0] += 1

    # result = []
    for k in data:
        v = data[k]
        data[k] = f"{k}={v['min']:.2f}/{v['sum'] / v['count']:.2f}/{v['max']:.2f}"
        # data[k] = f"{k}={v[0][0]:.2f}/{v[0][2] / v[1][0]:.2f}/{v[0][1]:.2f}"
    print(data)


def aggregate_with_pandas():
    df = pd.read_csv('../measurements.txt', sep=';', header=None, names=['City', 'Temperature'])
    result = df.groupby('City')['Temperature'].agg(['min', 'max', 'mean'])


def main():
    # start = time.time()
    # aggregate_with_pandas()
    # print(f"Aggregation with pandas took {time.time() - start} seconds")
    
    start = time.time()
    aggregate()
    print(f"Aggregation took {time.time() - start} seconds")


main()
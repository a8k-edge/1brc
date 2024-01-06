package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"time"
)

type City struct {
	min, max, total float64
	count           uint
}

func (c *City) String() string {
	return fmt.Sprintf("%.2f/%.2f/%.2f", c.min, c.total/float64(c.count), c.max)
}

func aggregate() {
	file, err := os.Open("../measurements.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	data := make(map[string]*City)
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, ";")
		if len(parts) != 2 {
			log.Fatalf("Invalid line format: %s", line)
		}

		name := parts[0]
		t, err := strconv.ParseFloat(parts[1], 64)
		if err != nil {
			log.Fatal(err)
		}

		city, exists := data[name]
		if !exists {
			city = &City{min: t, max: t, total: t, count: 1}
			data[name] = city
		} else {
			city.min = min(city.min, t)
			city.max = max(city.max, t)
			city.total += t
			city.count++
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}

	fmt.Println(data)
}

func min[T ~float64](a, b T) T {
	if a > b {
		return b
	}
	return a
}

func max[T ~float64](a, b T) T {
	if a > b {
		return a
	}
	return b
}

func main() {
	start := time.Now()
	aggregate()
	fmt.Println("Aggeregation took", time.Since(start))
}

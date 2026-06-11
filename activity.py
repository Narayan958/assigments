from typing import List, Dict, Set
from collections import defaultdict
from functools import reduce

def total_time_per_user(logs: List[Dict]) -> Dict[str, float]:
    """
    Computes total screen time per individual user.
    Uses defaultdict to efficiently aggregate durations.
    """
    user_time = defaultdict(float)
    for log in logs:
        user_time[log["user"]] += log["duration"]
    return dict(user_time)

def most_active_users(logs: List[Dict], k: int) -> List[str]:
    """
    Returns the top K most active users sorted by total duration in descending order.
    Uses sorted() with a lambda key.
    """
    totals = total_time_per_user(logs)
    
    sorted_users = sorted(totals.items(), key=lambda x: x[1], reverse=True)
    
    return [user for user, _ in sorted_users[:k]]

def unique_actions(logs: List[Dict]) -> Set[str]:
    """
    Returns a set of all unique actions found in the logs.
    Uses a set comprehension to satisfy requirement 3b.
    """
    return {log["action"] for log in logs}

def total_activity_time(logs: List[Dict]) -> float:
    """
    Computes the total activity time of all logs combined using reduce().
    Requirement 3f: reduce(function, iterable, initializer)
    """
    return reduce(lambda acc, log: acc + log["duration"], logs, 0.0)


if __name__ == "__main__":
    
    logs = [
        {"user": "adnar54", "action": "YouTube", "duration": 1.5},
        {"user": "Sahil01", "action": "Instagram", "duration": 2.0},
        {"user": "Rahul69", "action": "VSCode", "duration": 3.0},
        {"user": "adnar54", "action": "Google", "duration": 1.0}, 
        {"user": "Sahil01", "action": "WhatsApp", "duration": 0.5}, 
    ]
    print("Total time per users:", total_time_per_user(logs))
    print("Top 2 active users:", most_active_users(logs, 2))
    print("Unique actions:", unique_actions(logs))
    print("Total activity times:", total_activity_time(logs))
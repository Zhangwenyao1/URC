import click

@click.command()
@click.option('--lat', '-N', prompt='Latitude')
@click.option('--long', '-W', prompt='Longitude')
def gps_goal(lat, long):
    """Send goal to move_base given latitude and longitude

\b
Two usage formats:
gps_goal.py --lat 43,39,31 --long 79,22,45 # DMS format
gps_goal.py --lat 43.658 --long -79.379 # decimal format"""

    click.echo('Given: %sN, %sW!' % (lat,long))

if __name__ == '__main__':
    gps_goal()


// src/spotifyService.ts
import axios, { AxiosResponse } from 'axios';

const SPOTIFY_API_URL_BASE = 'https://api.spotify.com/v1';
const SPOTIFY_API_URL = 'https://api.spotify.com/v1/users/31ka3rwh4zeb5d64w42p35uyy5gu/playlists';

export class SpotifyService {
  private readonly clientId: string;
  private readonly clientSecret: string;
  private accessToken: string | null = null;

  constructor(clientId: string, clientSecret: string) {
    this.clientId = clientId;
    this.clientSecret = clientSecret;
  }

  async getAccessToken() {
    if (this.accessToken) {
      return this.accessToken;
    }

    try {
      const response = await axios.post(
        'https://accounts.spotify.com/api/token',
        'grant_type=client_credentials',
        {
          headers: {
            Authorization: `Basic ${Buffer.from(
              `${this.clientId}:${this.clientSecret}`
            ).toString('base64')}`,
            'Content-Type': 'application/x-www-form-urlencoded',
          },
        }
      );

      this.accessToken = response.data.access_token;
      return this.accessToken;
    } catch (error) {
      throw new Error('Failed to obtain access token');
    }
  }

  async getPlaylists() {
    const accessToken = await this.getAccessToken();

    try {
      const response: AxiosResponse = await axios.get(
        `${SPOTIFY_API_URL}`,
        {
          headers: {
            Authorization: `Bearer ${accessToken}`,
          },
        }
      );

      return response.data.items;
    } catch (error) {
      throw new Error('Failed to fetch albums');
    }
  }
}
